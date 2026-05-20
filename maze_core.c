// ソフトウェア工学 課題用修正1
#include "maze.h"

Maze *createMaze(int w, int h) {
  Maze *maze = (Maze *)malloc(sizeof(Maze));
  if (maze == NULL) {
    printf("メモリ確保に失敗しました\n");
    exit(1);
  }

  // サイズを記録
  maze->width = w; // ソフトウェア工学 課題用修正2
  maze->height = h;

  // プレイヤーの初期位置
  maze->playerX = 1; // プレイヤーのX座標を１に
  maze->playerY = 1; // プレイヤーのY座標を１に

  maze->map = (Cell **)malloc(sizeof(Cell *) * h);
  if (maze->map == NULL) {
    printf("メモリ確保に失敗しました\n");
    exit(1);
  }

  for (int y = 0; y < h; y++) {
    maze->map[y] = (Cell *)malloc(sizeof(Cell) * w);
    if (maze->map[y] == NULL) {
      printf("メモリ確保に失敗しました(%d行目)\n", y);
      exit(1);
    }

    maze->map[y] = (Cell *)malloc(sizeof(Cell) * w);
    if (maze->map[y] == NULL) {
      printf("メモリ確保に失敗しました(%d行目)\n", y);
      exit(1);
    }
  }
  return maze; // 完成した迷路データのポインタを返す
}

void freeMaze(Maze *maze) {
  if (maze == NULL)
    return;

  // 各行のマス目データを解放
  for (int y = 0; y < maze->height; y++) {
    free(maze->map[y]);
  }

  // 行ポインタの配列を解放
  free(maze->map);

  // 迷路構造体そのものを解放
  free(maze);
}

void drawMaze(const Maze *maze) {
  printf("\n");
  for (int y = 0; y < maze->height; y++) {
    for (int x = 0; x < maze->width; x++) {
      // プレイヤーの位置に 'P' を表示
      if (x == maze->playerX && y == maze->playerY) {
        printf("P ");
        continue; // 次のループへ
      }

      // それ以外はセルの種類によって文字を変える
      switch (maze->map[y][x].type) {
      case WALL:
        printf("##");
        break; // 壁
      case PATH:
        printf("  ");
        break; // 道
      case START:
        printf("S ");
        break; // スタート
      case GOAL:
        printf("G ");
        break; // ゴール
      case TRACK:
        printf("..");
        break; // 足跡
      default:
        printf("??");
        break;
      }
    }
    printf("\n"); // 1行表示し終わったら改行
  }
}

void movePlayer(Maze *maze, char key) {
  int dx = 0;
  int dy = 0;

  // キーを各方向に対応させる
  switch (key) {
  case 'w':
    dy = -1;
    break; // 上
  case 's':
    dy = 1;
    break; // 下
  case 'a':
    dx = -1;
    break; // 左
  case 'd':
    dx = 1;
    break; // 右
  default:
    return; // 無効なキーなら何もしない
  }

  // 移動先の座標を計算
  int nx = maze->playerX + dx;
  int ny = maze->playerY + dy;

  // 移動できるかチェック
  // 範囲外に出ていないか
  if (nx < 0 || nx >= maze->width || ny < 0 || ny >= maze->height) {
    return;
  }

  // 行く先が壁ではないか
  if (maze->map[ny][nx].type != WALL) {
    // 問題なければ、プレイヤーの座標を更新
    maze->playerX = nx;
    maze->playerY = ny;
  } else {
    printf("そこは壁です！\n");
  }
}