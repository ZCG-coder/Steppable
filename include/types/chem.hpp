#include <array>
#include <string>

namespace steppable::chem
{
    struct Element
    {
        int atomicNumber;
        std::string symbol;
        std::string name;
        float atomicMass;
        std::array<char, 6> cpkCol;
        std::string electronConf;
        float electroNeg;
        int atomicRadius;
        float ionizaEnergy;
        float electronAff;
        std::string oxidStates;
        std::string stdState;
        float meltPtK;
        float boilPtK;
        float density;
        std::string groupBlk;
        int yearDiscover;
        bool predicted;
        std::string electronShel;
        int numShells;

        std::string present() const { return symbol; }
    };

    struct Atom
    {
        Atom(const Element& elem, int neutrons = -1);

    private:
        Element elem;
        int protons = elem.atomicNumber;
        int neutrons = -1;
        int electrons = elem.atomicNumber;
    };

    struct Ion : private Atom
    {
        Ion(const Element& elem, int charge, int neutrons = -1);
    };
} // namespace steppable::chem
