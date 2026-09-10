





int count_neighbors(char *board, int x, int y, int w, int h){
    int count = 0;
    for (int dy = -1; dy <= 1; dy++){
        for (int dx = -1; dx <= 1; dx++){
            if (dx == 0 && dy == 0) continue ;

            int nx = dx + x;
            int ny = dy + y;

            if (nx >= 0 && nx < w && ny >= 0 && ny < h){
                if (board[idx(nx, ny, w)] == 'O'){
                    count++;
                }
            }
        }
    }
    return (count);
}
