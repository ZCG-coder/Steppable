/**************************************************************************************************
 * Copyright (c) 2023-2026 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

#pragma once

#include "steppable/number.hpp"
#include "stpSqlite.hpp"
#include "types/point.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace steppable::chem
{
    using STP_AtomCoord = _Vec3<Number>;

    class Subshell
    {
        Number order;
        char type;
        Number electrons;

        friend class Element;

    public:
        [[nodiscard]] std::string present() const { return order.present() + type + electrons.present(); }

        [[nodiscard]] Number getOrder() const { return order; }
        [[nodiscard]] char getType() const { return type; }
        [[nodiscard]] Number getElectrons() const { return electrons; }
    };

    class Element : sqlite::STP_DataConnectorBase
    {
        friend class Atom;

        Number atomicNumber;
        std::string symbol;
        std::string name;
        Number atomicMass;
        std::array<char, 6> cpkCol = {};
        std::vector<Subshell> electronConf;
        Number electroNeg;
        Number atomicRadius;
        Number ionizaEnergy;
        Number electronAff;
        std::string oxidStates;
        std::string stdState;
        Number meltPtK;
        Number boilPtK;
        Number density;
        std::string groupBlk;
        int yearDiscover = 0;
        bool predicted = false;
        std::vector<Number> electronShells;
        Number numShells;

    public:
        void initializeFromStmt(SQLite::Statement stmt);
        Element(int atomicNumber);

        Element(const std::string& symbol);

        [[nodiscard]] Number getAtomicNumber() const { return atomicNumber; }
        [[nodiscard]] std::string getSymbol() const { return symbol; }
        [[nodiscard]] std::string getName() const { return name; }
        [[nodiscard]] Number getAtomicMass() const { return atomicMass; }
        [[nodiscard]] std::array<char, 6> getCpkCol() const { return cpkCol; }
        [[nodiscard]] std::vector<Subshell> getElectronConf() const { return electronConf; }
        [[nodiscard]] Number getElectroNeg() const { return electroNeg; }
        [[nodiscard]] Number getAtomicRadius() const { return atomicRadius; }
        [[nodiscard]] Number getIonizaEnergy() const { return ionizaEnergy; }
        [[nodiscard]] Number getElectronAff() const { return electronAff; }
        [[nodiscard]] std::string getOxidStates() const { return oxidStates; }
        [[nodiscard]] std::string getStdState() const { return stdState; }
        [[nodiscard]] Number getMeltPtK() const { return meltPtK; }
        [[nodiscard]] Number getBoilPtK() const { return boilPtK; }
        [[nodiscard]] Number getDensity() const { return density; }
        [[nodiscard]] std::string getGroupBlk() const { return groupBlk; }
        [[nodiscard]] int getYearDiscover() const { return yearDiscover; }
        [[nodiscard]] bool getPredicted() const { return predicted; }
        [[nodiscard]] std::vector<Number> getElectronShel() const { return electronShells; }
        [[nodiscard]] Number getNumShells() const { return numShells; }

        [[nodiscard]] std::string present() const;
    };

    /**
     * @brief Types of chemical bonds.
     */
    enum class BondType : std::uint8_t
    {
        Single, ///< Single bond
        Double, ///< Double bond
        Triple, ///< Triple bond
        Ionic ///< Ionic bond
    };

    /**
     * @brief Represents a bond between two atoms.
     */
    class Bond
    {
    public:
        /**
         * @param atomIdx1 Index of the first atom.
         * @param atomIdx2 Index of the second atom.
         * @param type Type of the bond.
         */
        Bond(size_t atomIdx1, size_t atomIdx2, BondType type);

        /**
         * @return Index of the first atom.
         */
        [[nodiscard]] size_t getAtom1Index() const;

        /**
         * @return Index of the second atom.
         */
        [[nodiscard]] size_t getAtom2Index() const;

        /**
         * @return Bond type.
         */
        [[nodiscard]] BondType getType() const;

        /**
         * @brief Serialize to string.
         * @return Bond as a string.
         */
        [[nodiscard]] std::string toString() const;

        /**
         * @brief Deserialize from string.
         * @param str Bond as a string.
         * @return Bond instance.
         */
        static Bond fromString(const std::string& str);

    private:
        size_t atomIdx1, atomIdx2;
        BondType type;
    };

    /**
     * @brief Represents a chemical atom (with optional charge and coordinates).
     */
    class Atom
    {
    public:
        /**
         * @param symbol Element symbol.
         * @param atomicNumber Atomic number.
         * @param charge Formal charge.
         * @param coord 3D coordinate.
         */
        Atom(std::string symbol, Number atomicNumber, Number charge = Number(), STP_AtomCoord coord = { 0, 0, 0 });

        /**
         * @return Element symbol.
         */
        [[nodiscard]] const std::string& getSymbol() const;

        /**
         * @return Atomic number.
         */
        [[nodiscard]] Number getAtomicNumber() const;

        /**
         * @return Formal charge.
         */
        [[nodiscard]] Number getCharge() const;

        /**
         * @param charge New formal charge.
         */
        void setCharge(Number charge);

        /**
         * @param c 3D coordinate.
         */
        void setCoordinate(const STP_AtomCoord& c);

        /**
         * @return 3D coordinate.
         */
        [[nodiscard]] STP_AtomCoord getCoordinate() const;

        /**
         * @brief Serialize to SMILES.
         * @return Atom as SMILES string.
         */
        [[nodiscard]] std::string toSmiles() const;

        /**
         * @brief Serialize to MOL.
         * @return Atom as MOL string.
         */
        [[nodiscard]] std::string toMol() const;

        /**
         * @brief Deserialize from SMILES.
         * @param smiles SMILES string.
         * @return Atom instance.
         */
        static Atom fromSmiles(const std::string& smiles);

        /**
         * @brief Deserialize from MOL.
         * @param mol MOL string.
         * @return Atom instance.
         */
        static Atom fromMol(const std::string& mol);

    private:
        std::string symbol;
        Number atomicNumber;
        Number charge;
        STP_AtomCoord coordinate;
    };

    /**
     * @brief Represents a chemical molecule (collection of atoms and bonds).
     */
    class Molecule
    {
    public:
        /**
         * @param atom Atom to add.
         * @return Index of atom in this molecule.
         */
        size_t addAtom(const Atom& atom);

        /**
         * @param bond Bond to add.
         */
        void addBond(const Bond& bond);

        /**
         * @param idx Atom index.
         * @return Atom at the given index.
         */
        [[nodiscard]] const Atom& getAtom(size_t idx) const;

        /**
         * @return Vector of atoms.
         */
        [[nodiscard]] const std::vector<Atom>& getAtoms() const;

        /**
         * @return Vector of bonds.
         */
        [[nodiscard]] const std::vector<Bond>& getBonds() const;

        /**
         * @return Net charge of the molecule.
         */
        [[nodiscard]] Number getNetCharge() const;

        /**
         * @brief Serialize to SMILES.
         * @return Molecule as SMILES string.
         */
        [[nodiscard]] std::string toSmiles() const;

        /**
         * @brief Serialize to MOL.
         * @return Molecule as MOL string.
         */
        [[nodiscard]] std::string toMol() const;

        /**
         * @brief Deserialize from SMILES.
         * @param smiles SMILES string.
         * @return Molecule instance.
         */
        static Molecule fromSmiles(const std::string& smiles);

        /**
         * @brief Deserialize from MOL.
         * @param mol MOL string.
         * @return Molecule instance.
         */
        static Molecule fromMol(const std::string& mol);

    private:
        std::vector<Atom> atoms;
        std::vector<Bond> bonds;
    };

    /**
     * @brief Chemistry unit: single atom/ion or molecule/polyatomic ion.
     */
    class CompoundUnit
    {
    public:
        /**
         * @param atom Atom to construct unit.
         */
        CompoundUnit(const Atom& atom);

        /**
         * @param mol Molecule to construct unit.
         */
        CompoundUnit(const Molecule& mol);

        /**
         * @return True if unit is atom.
         */
        [[nodiscard]] bool isAtom() const;

        /**
         * @return Atom if unit is atom.
         */
        [[nodiscard]] const Atom& getAtom() const;

        /**
         * @return Molecule if unit is molecule.
         */
        [[nodiscard]] const Molecule& getMolecule() const;

        /**
         * @return Net charge.
         */
        [[nodiscard]] Number getNetCharge() const;

        /**
         * @brief Serialize to SMILES.
         * @return Unit as SMILES string.
         */
        [[nodiscard]] std::string toSmiles() const;

        /**
         * @brief Serialize to MOL.
         * @return Unit as MOL string.
         */
        [[nodiscard]] std::string toMol() const;

        /**
         * @brief Deserialize from SMILES.
         * @param smiles SMILES string.
         * @return CompoundUnit instance.
         */
        static CompoundUnit fromSmiles(const std::string& smiles);

        /**
         * @brief Deserialize from MOL.
         * @param mol MOL string.
         * @return CompoundUnit instance.
         */
        static CompoundUnit fromMol(const std::string& mol);

    private:
        std::variant<Atom, Molecule> unit;
    };

    /**
     * @brief Chemical combination (compound), e.g., NaCl, CaCl2.
     */
    class Compound
    {
    public:
        /**
         * @param unit CompoundUnit to add.
         * @param count Number of times to add unit.
         */
        void addUnit(const CompoundUnit& unit, Number count = Number(1));

        /**
         * @return Units of compound and their multiplicities.
         */
        [[nodiscard]] const std::vector<std::pair<CompoundUnit, Number>>& getUnits() const;

        /**
         * @return Net charge of compound.
         */
        [[nodiscard]] Number getNetCharge() const;

        /**
         * @brief Serialize to SMILES.
         * @return Compound as SMILES string.
         */
        [[nodiscard]] std::string toSmiles() const;

        /**
         * @brief Serialize to MOL (SDF-style for units).
         * @return Compound as MOL/SDF string.
         */
        [[nodiscard]] std::string toMol() const;

        /**
         * @brief Deserialize from SMILES.
         * @param smiles SMILES string.
         * @return Compound instance.
         */
        static Compound fromSmiles(const std::string& smiles);

        /**
         * @brief Deserialize from MOL/SDF.
         * @param mol MOL/SDF string.
         * @return Compound instance.
         */
        static Compound fromMol(const std::string& mol);

    private:
        std::vector<std::pair<CompoundUnit, Number>> units;
    };
} // namespace steppable::chem
