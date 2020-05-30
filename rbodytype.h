#ifndef RBODYTYPE_H
#define RBODYTYPE_H

/**
 * Liste de tous les RigidBody
 * [!] Attention à ne pas changer l'ordre sinon ça défonce toutes les maps déjà faites :(
 */
enum RBodyType {
    pGrassPlatform,
    pSandPlatform,
    pDirtPlatform,
    pSnowPlatform,
    pStonePlatform,
    pCastlePlatform,
    tWater,
    tLava,
    tBoxCoin,
    tBoxItem,
    tBoxEmpty,
    tBox,
    tBoxAlt,
    tSpikes,
    tSpring,
    tLever,
    iCoinBronze,
    iCoinSilver,
    iCoinGold,
    eBlocker,
    eFish,
    eSlime,
    ePoker,
    eSnail,
    dSignExit,
    dSignLeft,
    dSignRight,
    dBush,
    dRock,
    dSnowhill,
    dPlantPurple,
    dPlant,
    dCactus,
    dCloud,
    eFly,
    ePlayer,
};

#endif // RBODYTYPE_H
