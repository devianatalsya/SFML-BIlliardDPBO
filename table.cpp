// ==============================================
// FILE: Table.cpp
// PENANGGUNG JAWAB: NADINE & FATHYA
// ==============================================
#include "Table.h"

Table::Table(float w, float h) : width(w), height(h)
{
    // Inisialisasi 6 lubang (4 corner + 2 side)
    float pocketRadius = 25.0f;
    float margin = 30.0f;

    // 4 Corner pockets
    pockets.push_back(Pocket(margin, margin, pocketRadius));                  // Top-left
    pockets.push_back(Pocket(width - margin, margin, pocketRadius));          // Top-right
    pockets.push_back(Pocket(margin, height - margin, pocketRadius));         // Bottom-left
    pockets.push_back(Pocket(width - margin, height - margin, pocketRadius)); // Bottom-right

    // 2 Side pockets
    pockets.push_back(Pocket(width / 2, margin, pocketRadius));          // Top-middle
    pockets.push_back(Pocket(width / 2, height - margin, pocketRadius)); // Bottom-middle
}