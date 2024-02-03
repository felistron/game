#include "stdio.h"
#include "time.h"
#include "raylib.h"

#define WIDTH 800
#define HEIGHT WIDTH
#define TITLE "Game of life in c"

#define N_CELLS 100
#define CELLS_COUNT N_CELLS * N_CELLS
#define CELL_SIZE WIDTH / N_CELLS

int cells[CELLS_COUNT];
int heatMap[CELLS_COUNT];
int maxHeat = 1;

bool paused = false;
bool heatmapActive = false;
bool grid = false;

void updateState() {
  int copy[CELLS_COUNT];

  for (size_t i = 0; i < CELLS_COUNT; i++) {
    // search for neighbors
    size_t liveNeighbors = 0;
    copy[i] = cells[i];

    for (size_t j = 0; j < 9; j++) {
      // relative position to cells[i] cell
      int relativeX = j % 3 - 1;
      int relativeY = j / 3 - 1;

      if (relativeX == 0 && relativeY == 0) continue;

      int cx = i % N_CELLS + relativeX;
      int cy = i / N_CELLS + relativeY;

      if (cx >= N_CELLS) cx = 0;
      if (cy >= N_CELLS) cy = 0;
      if (cx < 0) cx = N_CELLS - 1;
      if (cy < 0) cy = N_CELLS - 1;

      //printf("Cell at [%ld] has neighbor [%d, %d] = [%d, %d] -> %d\n", i, relativeX, relativeY, cx, cy, 0);

      int k = cy * N_CELLS + cx;

      if (cells[k] == 1) {
        liveNeighbors++;
      }
    }

    if (cells[i] == 1) {
      //printf("Live neighbors of %ld: %ld\n", i, liveNeighbors);
      // underpopulation
      if (liveNeighbors < 2) copy[i] = 0;

      // overpopulation
      if (liveNeighbors > 3) copy[i] = 0;
    } else {
      // reproduction
      if (liveNeighbors == 3) copy[i] = 1;
    }
  }

  for (size_t i = 0; i < CELLS_COUNT; i++) {
    int diff = cells[i] - copy[i];

    if (diff != 0) {
      heatMap[i] += 1;
    }

    if (heatMap[i] > maxHeat) {
      maxHeat = heatMap[i];
    }

    cells[i] = copy[i];
  }
}

int main(void) {
  SetRandomSeed(time(NULL));

  for (size_t i = 0; i < CELLS_COUNT; i++) {
    cells[i] = GetRandomValue(0, 1);
  }

  float count = 0;

  SetTargetFPS(60);

  InitWindow(WIDTH, HEIGHT, TITLE);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (IsMouseButtonDown(0)) {
      Vector2 mousePos = GetMousePosition();
      int x = mousePos.x / (CELL_SIZE);
      int y = mousePos.y / (CELL_SIZE);
      int i = N_CELLS * y + x;

      cells[i] = 1;
    }

    if (IsKeyPressed(KEY_R)) {
      for (size_t i = 0; i < CELLS_COUNT; i++) {
        heatMap[i] = 0;
        cells[i] = GetRandomValue(0, 1);
      }
      maxHeat = 1;
    }

    if (IsKeyPressed(KEY_C)) {
      for (size_t i = 0; i < CELLS_COUNT; i++) {
        heatMap[i] = 0;
        cells[i] = 0;
      }
      maxHeat = 1;
    }

    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }

    if (IsKeyPressed(KEY_H)) {
      heatmapActive = !heatmapActive;
    }

    if (IsKeyPressed(KEY_G)) {
      grid = !grid;
    }

    if (IsKeyPressed(KEY_ENTER)) {
      updateState();
    }

    if (!paused) {
      count += GetFrameTime();

      if (count > 0.01f) {
        count = 0;
        updateState();
      }
    }

    for (size_t i = 0; i < CELLS_COUNT; i++) {
      int x = (i * CELL_SIZE) % WIDTH;
      int y = (i * CELL_SIZE) / WIDTH * CELL_SIZE;


      if (grid) {
        Color gridColor = ColorFromHSV(0, 0, 0.25f);
        DrawLine(x + CELL_SIZE, y, x + CELL_SIZE, y + CELL_SIZE, gridColor);
        DrawLine(x, y + CELL_SIZE, x + CELL_SIZE, y + CELL_SIZE, gridColor);
      }

      if (heatmapActive) {
        float heat = (float)heatMap[i] / (float)maxHeat;
        Color heatColor = ColorFromHSV(heat * 360, 0.7f, 1.0f);
        DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, heatColor);
      } else {
        if (cells[i] == 1) {
          DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, WHITE);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
