#include "raylib.h"
#include <iostream>

void DrawStatusScreen() {
        //MissionBoard
        DrawLine(screenWidth / 75, screenHeight / 9, screenWidth / 5, screenHeight / 9, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 5, screenWidth / 5, screenHeight / 5, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 9, screenWidth / 75, screenHeight / 5, WHITE);
        DrawLine(screenWidth / 5, screenHeight / 9, screenWidth / 5, screenHeight / 5, WHITE);

        DrawTextEx(Saga, "Mission Board", {screenWidth / 51.06, screenHeight / 7.50f}, ((screenHeight / 5.63f)-(screenHeight / 7.50f)), 1, WHITE);

        //Market
        DrawLine(screenWidth / 75, screenHeight / 3.75f, screenWidth / 5, screenHeight / 3.75f, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 2.81f, screenWidth / 5, screenHeight / 2.81f, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 3.75f, screenWidth / 75, screenHeight / 2.81f, WHITE);
        DrawLine(screenWidth / 5, screenHeight / 3.75f, screenWidth / 5, screenHeight / 2.81f, WHITE);

        DrawTextEx(Saga, "Market", {screenWidth / 51.06, screenHeight / 3.46f}, ((screenHeight / 5.63f)-(screenHeight / 7.50f)), 1, WHITE);

        //Status
        DrawLine(screenWidth / 75, screenHeight / 2.37f, screenWidth / 5, screenHeight / 2.37f, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 1.96f, screenWidth / 5, screenHeight / 1.96f, WHITE);
        DrawLine(screenWidth / 75, screenHeight / 2.37f, screenWidth / 75, screenHeight / 1.96f, WHITE);
        DrawLine(screenWidth / 5, screenHeight / 2.37f, screenWidth / 5, screenHeight / 1.96f, WHITE);

        DrawTextEx(Saga, "Status", {screenWidth / 51.06, screenHeight / 2.25f}, ((screenHeight / 5.63f)-(screenHeight / 7.50f)), 1, WHITE);

        //Pilot
        DrawLine(screenWidth / 4, screenHeight / 9, screenWidth / 1.78f, screenHeight / 9, WHITE);
        DrawLine(screenWidth / 4, screenHeight / 2.25f, screenWidth / 1.78f, screenHeight / 2.25f, WHITE);
        DrawLine(screenWidth / 4, screenHeight / 9, screenWidth / 4, screenHeight / 2.25f, WHITE);
        DrawLine(screenWidth / 1.78f, screenHeight / 9, screenWidth / 1.78f, screenHeight / 2.25f, WHITE);

        DrawTextEx(Saga, "Pilot: XYZ", {screenWidth / 3.72f, screenHeight / 6.92f}, ((screenHeight / 5.17f)-(screenHeight / 6.92f)), 1, WHITE);
        DrawTextEx(Saga, "Registered Pilot Under", {screenWidth / 3.72f, screenHeight / 4.41f}, ((screenHeight / 3.85f)-(screenHeight / 4.41f)), 1, WHITE);
        DrawTextEx(Saga, "the SSE Administration", {screenWidth / 3.72, screenHeight / 3.69f}, ((screenHeight / 3.28f)-(screenHeight / 3.69f)), 1, WHITE);
        DrawTextEx(Saga, "License Valid Until: 04/14/2248", {screenWidth / 3.72f, screenHeight / 2.96f}, ((screenHeight / 2.78f)-(screenHeight / 2.96f)), 1, WHITE);
        DrawTextEx(Saga, "Birthdate:           09/12/2223", {screenWidth / 3.72f, screenHeight / 2.72f}, ((screenHeight / 2.57f)-(screenHeight / 2.73f)), 1, WHITE);

        //Ship
        DrawLine(screenWidth / 1.60f, screenHeight / 9, screenWidth / 1.07f, screenHeight / 9, WHITE);
        DrawLine(screenWidth / 1.60f, screenHeight / 2.25f, screenWidth / 1.07f, screenHeight / 2.25f, WHITE);
        DrawLine(screenWidth / 1.60f, screenHeight / 9, screenWidth / 1.60f, screenHeight / 2.25f, WHITE);
        DrawLine(screenWidth / 1.07f, screenHeight / 9, screenWidth / 1.07f, screenHeight / 2.25f, WHITE);

        DrawTextEx(Saga, "Ship", {screenWidth / 1.55f, screenHeight / 6.92f}, ((screenHeight / 5.17f)-(screenHeight / 6.92f)), 1, WHITE);
        DrawTextEx(Saga, "Weapon LVL: Level", {screenWidth / 1.55f, screenHeight / 4.25f}, ((screenHeight / 3.72f)-(screenHeight / 4.25f)), 1, WHITE);
        DrawTextEx(Saga, "Shield LVL: Level", {screenWidth / 1.55f, screenHeight / 3.57f}, ((screenHeight / 3.19f)-(screenHeight / 3.57f)), 1, WHITE);
        DrawTextEx(Saga, "Gathering Tool LVL: Level", {screenWidth / 1.55f, screenHeight / 3.08f}, ((screenHeight / 2.80f)-(screenHeight / 3.08f)), 1, WHITE);
        DrawTextEx(Saga, "Overal Speed: Speed", {screenWidth / 1.55f, screenHeight / 2.71f}, ((screenHeight / 2.49f)-(screenHeight / 2.71f)), 1, WHITE);

        //Debt
        DrawLine(screenWidth / 4, screenHeight / 1.80f, screenWidth / 1.28f, screenHeight / 1.80f, WHITE);
        DrawLine(screenWidth / 4, screenHeight / 1.13f, screenWidth / 1.28f, screenHeight / 1.13f, WHITE);
        DrawLine(screenWidth / 4, screenHeight / 1.80f, screenWidth / 4, screenHeight / 1.13f, WHITE);
        DrawLine(screenWidth / 1.28f, screenHeight / 1.80f, screenWidth / 1.28f, screenHeight / 1.13f, WHITE);

        DrawTextEx(Saga, "This pilot is to pay of their debt to MORT CORP by", {screenWidth / 3.72f, screenHeight / 1.70f}, ((screenHeight / 1.63f)-(screenHeight / 1.70f)), 1, WHITE);
        DrawTextEx(Saga, "08/28/2242", {screenWidth / 3.72f, screenHeight / 1.61f}, ((screenHeight / 1.55f)-(screenHeight / 1.61f)), 1, WHITE);
        DrawTextEx(Saga, "for the loan of borrowed limbs or shall forfeit their life", {screenWidth / 3.72f, screenHeight / 1.54f}, ((screenHeight / 1.48f)-(screenHeight / 1.54f)), 1, WHITE);
        DrawTextEx(Saga, "and body for scientific and good purposes.", {screenWidth / 3.72f, screenHeight / 1.47f}, ((screenHeight / 1.42f)-(screenHeight / 1.47f)), 1, WHITE);
        DrawTextEx(Saga, "MORT CORP is protected under the Right to", {screenWidth / 3.72f, screenHeight / 1.35f}, ((screenHeight / 1.31f)-(screenHeight / 1.35f)), 1, WHITE);
        DrawTextEx(Saga, "Dismemberment Act and the Right to Slay Act.", {screenWidth / 3.72f, screenHeight / 1.30f}, ((screenHeight / 1.26f)-(screenHeight / 1.30f)), 1, WHITE);
        DrawTextEx(Saga, "Debt owed to MORT CORP: Debt", {screenWidth / 3.72f, screenHeight / 1.21f}, ((screenHeight / 1.17f)-(screenHeight / 1.21f)), 1, WHITE);
}
