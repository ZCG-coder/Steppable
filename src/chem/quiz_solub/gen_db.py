#####################################################################################################
#  Copyright (c) 2023-2026 NWSOFT                                                                   #
#                                                                                                   #
#  Permission is hereby granted, free of charge, to any person obtaining a copy                     #
#  of this software and associated documentation files (the "Software"), to deal                    #
#  in the Software without restriction, including without limitation the rights                     #
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                        #
#  copies of the Software, and to permit persons to whom the Software is                            #
#  furnished to do so, subject to the following conditions:                                         #
#                                                                                                   #
#  The above copyright notice and this permission notice shall be included in all                   #
#  copies or substantial portions of the Software.                                                  #
#                                                                                                   #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                       #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                         #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                      #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                           #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                    #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                    #
#  SOFTWARE.                                                                                        #
#####################################################################################################

import random
import re
import sqlite3
from math import gcd

from lib.paths import DATA_DIR

ION_FMLA = re.compile(r"\[([A-Za-z0-9]+)\]([0-9]*)([+-])")
SIMPLE_ION_RE = re.compile(r"^[A-Z][a-z]*$")

anions = [
    "[F]-",
    "[Cl]-",
    "[Br]-",
    "[I]-",
    "[ClO3]-",
    "[OH]-",
    "[SO3]2-",
    "[SO4]2-",
    "[CO3]2-",
    "[NO2]-",
    "[NO3]-",
    "[PO4]3-",
    "[HCO3]-",
]

cations = [
    "[Mg]2+",
    "[Ca]2+",
    "[Ba]2+",
    "[Ag]+",
    "[Pb]2+",
    "[Na]+",
    "[K]+",
    "[Li]+",
    "[Fe]3+",
    "[Fe]2+",
    "[NH4]+",
    "[Cu]2+",
    "[Zn]2+",
    "[Al]3+",
]

impossible_compounds = [
    "FeI3",
    "CuI2",
    "AgOH",
    "NH4OH",
    "NH4ClO3",
    "NH4NO2",
    "Mg(HCO3)2",
    "Ca(HCO3)2",
    "Ba(HCO3)2",
    "AgHCO3",
    "Pb(HCO3)2",
    "Fe(HCO3)2",
    "Fe(HCO3)3",
    "Cu(HCO3)2",
    "Zn(HCO3)2",
    "Al(HCO3)3",
    "Al2(CO3)3",
    "Fe2(CO3)3",
    "Fe2(SO3)3",
    "Fe(NO2)3",
    "Al2(SO3)3",
]

soluble = [
    "AgF",
    "NaF",
    "KF",
    "LiF",
    "FeF3",
    "FeF2",
    "NH4F",
    "CuF2",
    "ZnF2",
    "MgCl2",
    "CaCl2",
    "BaCl2",
    "NaCl",
    "KCl",
    "LiCl",
    "FeCl3",
    "FeCl2",
    "NH4Cl",
    "CuCl2",
    "ZnCl2",
    "AlCl3",
    "MgBr2",
    "CaBr2",
    "BaBr2",
    "NaBr",
    "KBr",
    "LiBr",
    "FeBr3",
    "FeBr2",
    "NH4Br",
    "CuBr2",
    "ZnBr2",
    "AlBr3",
    "MgI2",
    "CaI2",
    "BaI2",
    "NaI",
    "KI",
    "LiI",
    "FeI2",
    "NH4I",
    "ZnI2",
    "AlI3",
    "Mg(ClO3)2",
    "Ca(ClO3)2",
    "Ba(ClO3)2",
    "AgClO3",
    "Pb(ClO3)2",
    "NaClO3",
    "KClO3",
    "LiClO3",
    "Fe(ClO3)3",
    "Fe(ClO3)2",
    "Cu(ClO3)2",
    "Zn(ClO3)2",
    "Al(ClO3)3",
    "Ca(OH)2",
    "Ba(OH)2",
    "NaOH",
    "KOH",
    "LiOH",
    "Na2SO3",
    "K2SO3",
    "Li2SO3",
    "(NH4)2SO3",
    "MgSO4",
    "CaSO4",
    "Na2SO4",
    "K2SO4",
    "Li2SO4",
    "Fe2(SO4)3",
    "FeSO4",
    "(NH4)2SO4",
    "CuSO4",
    "ZnSO4",
    "Al2(SO4)3",
    "Na2CO3",
    "K2CO3",
    "Li2CO3",
    "(NH4)2CO3",
    "Mg(NO2)2",
    "Ca(NO2)2",
    "Ba(NO2)2",
    "AgNO2",
    "Pb(NO2)2",
    "NaNO2",
    "KNO2",
    "LiNO2",
    "Fe(NO2)2",
    "Cu(NO2)2",
    "Zn(NO2)2",
    "Al(NO2)3",
    "Mg(NO3)2",
    "Ca(NO3)2",
    "Ba(NO3)2",
    "AgNO3",
    "Pb(NO3)2",
    "NaNO3",
    "KNO3",
    "LiNO3",
    "Fe(NO3)3",
    "Fe(NO3)2",
    "NH4NO3",
    "Cu(NO3)2",
    "Zn(NO3)2",
    "Al(NO3)3",
    "Na3PO4",
    "K3PO4",
    "Li3PO4",
    "(NH4)3PO4",
    "NaHCO3",
    "KHCO3",
    "LiHCO3",
    "NH4HCO3",
]

HTML_OUTPUT = True


class Ion:
    _fmla: str
    _charge: int

    def __init__(self, fmla: str, charge: int) -> None:
        self._fmla = fmla
        self._charge = charge


def str_to_ion(ionic_fmla: str, consider_sign: bool = True) -> Ion:
    matches = ION_FMLA.match(ionic_fmla)
    assert matches

    fmla = matches.group(1)
    charge = matches.group(2)
    sign = matches.group(3)
    if not charge:
        charge = "1"
    charge = int(charge)

    if sign == "-" and consider_sign:
        charge = -charge

    return Ion(fmla, charge)


def format_ion(fmla: str, count: int) -> str:
    if count == 1:
        return fmla

    if SIMPLE_ION_RE.fullmatch(fmla):
        return f"{fmla}{count}"
    else:
        return f"({fmla}){count}"


idx = 0

output = f"""
<style>
ol {{
    line-height: 2;
    padding-bottom: 0.125in;
}}

table {{
    width: 100%;
}}

p.horizontal-line {{
    width: 100%;
    border-bottom: 0.5pt solid #000;
}}

p.flipped {{
    transform: rotate(180deg);
}}
</style>

<h1>Solubility rules</h1>
<table>
    <td>Name:</td>
    <td>{"_" * 20}</td>
    <td>Date:</td>
    <td>{"_" * 20}</td>
    <td>Score:</td>
    <td>{"_" * 10}/161</td>
</table>

<ol>"""

items = []
for anion in anions:
    anion_obj = str_to_ion(anion, consider_sign=False)
    anion_charge = anion_obj._charge
    anion_fmla = anion_obj._fmla

    for cation in cations:
        cation_obj = str_to_ion(cation)
        cation_charge = cation_obj._charge
        cation_fmla = cation_obj._fmla

        g = gcd(cation_charge, anion_charge)
        cation_count = anion_charge // g
        anion_count = cation_charge // g

        compound = ""
        compound += format_ion(cation_fmla, cation_count)
        compound += format_ion(anion_fmla, anion_count)

        if compound in impossible_compounds:
            continue

        idx += 1

        is_soluble = compound in soluble

        if HTML_OUTPUT:
            compound = re.sub(r"([0-9]+?)", r"<sub>\1</sub>", compound)

        item = (
            f"<li>Is <strong>{compound}</strong> soluble in H<sub>2</sub>O?<br>" + "\n"
        )
        item += "<p class='horizontal-line'></p>\n"
        item += f"<p class='flipped'>{"Yes" if is_soluble else "No"}</p>\n"
        item += "</li>"

        items.append(item)

random.shuffle(items)
output += "\n".join(items)
output += "</ol>"
print(output)
