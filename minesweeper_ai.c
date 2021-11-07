#include "minesweeper_ai.h"

/*
    Gå igenom hela fältet och lägg ut flaggor eller öppna celler.

    Att lägga ut flagga:
        Om en cell har lika många gömda grannar som grannbomber,
        flagga alla grannar, annars låt vara.
    
    Att öppna celler:
        Om en cell har lika många flaggade grannar som grannbomber,
        öppna alla oflaggade, annars låt vara.
*/