#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_SNE : public Instruction {
public:
    explicit Instr_SNE(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext &context) override {
        setContext(context);

        switch (getModifier()) {
            case A:
                if (context.getAPtrForRead()->getAaddress() != context.getBPtrForRead()->getAaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case B:
                if (context.getAPtrForRead()->getBaddress() != context.getBPtrForRead()->getBaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case AB:
                if (context.getAPtrForRead()->getAaddress() != context.getBPtrForRead()->getBaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case BA:
                if (context.getAPtrForRead()->getBaddress() != context.getBPtrForRead()->getAaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case F:
                if ((context.getAPtrForRead()->getAaddress() != context.getBPtrForRead()->getAaddress()) &&
                    (context.getAPtrForRead()->getBaddress() != context.getBPtrForRead()->getBaddress()))
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            case X:
                if ((context.getAPtrForRead()->getBaddress() != context.getBPtrForRead()->getAaddress()) &&
                    (context.getAPtrForRead()->getAaddress() != context.getBPtrForRead()->getBaddress()))
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            case I:
                if ((context.getAPtrForRead()->get_opc() != context.getBPtrForRead()->get_opc()) &&
                    (context.getAPtrForRead()->getModifier() != context.getBPtrForRead()->getModifier()) &&
                    (context.getAPtrForRead()->getAMode() != context.getBPtrForRead()->getAMode()) &&
                    (context.getAPtrForRead()->getAaddress() != context.getBPtrForRead()->getAaddress()) &&
                    (context.getAPtrForRead()->getBMode() != context.getBPtrForRead()->getBMode()) &&
                    (context.getAPtrForRead()->getBaddress() != context.getBPtrForRead()->getBaddress()))
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            default:
                throw std::invalid_argument("Invalid modifier!!!");
        }
        context.popWarriorQueue();
    }

    std::string get_opc() const override {
        return std::string("SNE");
    }


    void print() const override {
        std::cout << "SNE";
        Instruction::print();
    }
};


namespace {
    Instruction *create_SNE(const InstructionData &idata) {
        return new Instr_SNE(idata);
    }


    bool b = Factory::getInstance()->
            registerFunction("SNE", create_SNE);
}
