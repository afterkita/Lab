#include <iostream>

class Language
{
public:
    virtual ~Language() = default;
    virtual std::string how_generate_code() const = 0;
};

class JAVA : public Language
{
public:
    std::string how_generate_code() const override
    {
        return "generated java code";
    }
};
class RUST : public Language
{
public:
    std::string how_generate_code() const override
    {
        return "generated rust code";
    }
};

class C_PLUS_PLUS : public Language
{
public:
    std::string how_generate_code() const override
    {
        return "generated C++ code";
    }
};
class C_sharp : public Language
{
public:
    std::string how_generate_code() const override
    {
        return "generated C# code";
    }
};

class PHP : public Language
{
public:
    std::string how_generate_code() const override
    {
        return "generated PHP code";
    }
};

class CodeGenerator
{
public:
    CodeGenerator(Language* language) { m_language=language; }
    std::string generateCode()
    {
        if (m_language)
            return m_language->how_generate_code();
        else
            throw new std::logic_error("Bad language");
    }
    std::string some_Code_Related_Thing()
    {
        return generateCode();
    }

    ~CodeGenerator() {delete m_language;}

private:
    Language* m_language;
};

int main()
{
    CodeGenerator generatorJava(new JAVA);
    CodeGenerator generatorPHP(new PHP);
    CodeGenerator generatorRust(new RUST);
    CodeGenerator generatorC_Sharp(new C_sharp);
    std::cout << generatorJava.generateCode() << "\n";
    std::cout << generatorRust.generateCode() << "\n";
    std::cout << generatorPHP.generateCode() << "\n";
    std::cout << generatorC_Sharp.generateCode() << "\n";
}