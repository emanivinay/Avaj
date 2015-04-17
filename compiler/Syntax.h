/**
 * A statement is a single logical step of execution. Each method consists of a
 * series of statements, which are to be executed in order.
 */
class Statement
{
public:
    virtual void run() = 0;
};


class Expression: public Statement
{
private:
public:
    virtual Object eval() = 0;

    void run()
    {
        Object obj = eval();
    }
};


class Assignment: public Statement
{
private:
    Variable var;
    Expression expr;
};
