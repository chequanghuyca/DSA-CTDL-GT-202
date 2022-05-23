#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

int** init_board()
{
    int** t = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if (i == 0)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        if (i == 4)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
    }
    t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
    t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;
    return t;
}

int** copy_board(int** board)
{
    int** n_b = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}

void print_board(int** board)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[4 - i][j] == 1)
                cout << "X ";
            else if (board[4 - i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

struct Position
{
    int x; int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a; y = b;
    }
};

struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s; pos_end = e;
    }
};
void init(int** temp, int** board);

int** init_marked();

void print_board(int** board, int** previous);

vector<Position> Positionaround(Position x);

vector<Move> get_valid_moves(int** board, int player);

vector<Move> get_valid_moves(int** current_board, int** previous_board, int player);

vector<Position> ganh(int** board, Move m, int player);

vector<Position> vay(int** board, Move m, int player);

Move select_move(int** current_board, int** previous_board, int player);

vector<Move> bay_or_mo(int** current_board, int** previous_board, int player);

int score(int** board, Move m, int player);

bool endgame(int** board, Move m, int player);

Move move_another(int** current_board, int** previous_board, int player);

void act_move(int** board, Move m, int player);

void act_move_another(int** board, int** previous_board, Move m, int player);

int minimax(int** current_board, int** previous_board, Move m, int alpha, int beta, int depth, int player);

void play(int first, int** previous_board, int** current_board) {
    int count = 0, limit = 20;
    int player;
    if (first == 1)
        player = 1;
    else
        player = -1;

    print_board(current_board, previous_board);
    cout << endl;
    while (count < limit)
    {
        count++;
        vector<Move> valid_moves = get_valid_moves(current_board, previous_board, player);
        if (valid_moves.size() != 0)
        {
            if (player == 1)
            {
                int** temp_current = init_marked();

                int** temp_previous = init_marked();

                init(temp_current, current_board);
                init(temp_previous, previous_board);

                Move slmove = select_move(current_board, previous_board, 1);

                init(current_board, temp_current);
                init(previous_board, temp_previous);

                act_move_another(current_board, previous_board, slmove, 1);
            }
            else
            {
                Move vad_move = valid_moves[0];
                act_move_another(current_board, previous_board, vad_move, -1);
            }

            print_board(current_board, previous_board);
            cout << endl;
        }

        else
            break;

        player *= -1;
    }
}

int main() {
    int sub_board[5][5] = { 0,  0, 0, 0, 0,
                           0,  0, 0, 0, 0,
                           1,  0, 0, 0, 0,
                           0,  1, 1, 0, 0,
                          -1, -1, 1, 0, 0 };

    int** board = new int* [5];
    for (int i = 0; i < 5; i++) {
        board[i] = new int[5];
        for (int j = 0; j < 5; j++) board[i][j] = sub_board[i][j];
    }

    Position start(2, 0), end(3, 0);
   
    Move m(start, end);

    print_board(board);

    vector<Position> vay_move = vay(board, m, 1);

    cout << vay_move.size() << "\n";
    
    act_move(board, m, 1);

    int sub_board2[5][5] = { 0,  0 ,  0, 0, 0,
                             0,  0 ,  0, 0, 0,
                             1,  1 ,  0, 0, 0,
                            -1,  1 ,  1, 1, 0,
                            -1,  0 , -1, 1, 0 };
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) board[i][j] = sub_board2[i][j];

    print_board(board);

    Position start2(3, 2), end2(4, 1);
   
    Move m2(start2, end2);

    vector<Position> vay_move2 = vay(board, m2, 1);
    
    cout << vay_move2.size() << "\n";
    
    act_move(board, m2, 1);

    int sub_board3[5][5] = { 0,  0 ,  0, 0,  0,
                             1,  1 ,  1, 1,  1,
                            -1, -1 , -1, 0, -1,
                             1,  1 ,  1, 1,  0,
                             0,  0 ,  0, 0,  0 };
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) board[i][j] = sub_board3[i][j];

    print_board(board);

    Position start3(1, 3), end3(2, 3);
   
    Move m3(start3, end3);

    vector<Position> vay_move3 = vay(board, m3, 1);
    
    cout << vay_move3.size() << "\n";
    
    act_move(board, m3, 1);

    return 0;
}

vector<Move> get_valid_moves(int** board, int player) {
    
    vector<Move> valid;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == player) {
                Position start(i, j);

                if (i - 1 >= 0) {
                    if (board[i - 1][j] != 1 && board[i - 1][j] != -1) {
                        Position end(i - 1, j);
                        Move temp(start, end);
                        valid.push_back(temp);
                    }
                }

                if (i + 1 <= 4) {
                    if (board[i + 1][j] != 1 && board[i + 1][j] != -1) {
                        Position end(i + 1, j);
                        Move temp(start, end);
                        valid.push_back(temp);
                    }
                }

                if (j - 1 >= 0) {
                    if (board[i][j - 1] != 1 && board[i][j - 1] != -1) {
                        Position end(i, j - 1);
                        Move temp(start, end);
                        valid.push_back(temp);
                    }
                }

                if (j + 1 <= 4) {
                    if (board[i][j + 1] != 1 && board[i][j + 1] != -1) {
                        Position end(i, j + 1);
                        Move temp(start, end);
                        valid.push_back(temp);
                    }
                }

                if ((i + j) % 2 == 0) {
                    if (i + 1 <= 4 && j + 1 <= 4) {
                        if (board[i + 1][j + 1] != 1 && board[i + 1][j + 1] != -1) {
                            Position end(i + 1, j + 1);
                            Move temp(start, end);
                            valid.push_back(temp);
                        }
                    }

                    if (i - 1 >= 0 && j + 1 <= 4) {
                        if (board[i - 1][j + 1] != 1 && board[i - 1][j + 1] != -1) {
                            Position end(i - 1, j + 1);
                            Move temp(start, end);
                            valid.push_back(temp);
                        }
                    }

                    if (i - 1 >= 0 && j - 1 >= 0) {
                        if (board[i - 1][j - 1] != 1 && board[i - 1][j - 1] != -1) {
                            Position end(i - 1, j - 1);
                            Move temp(start, end);
                            valid.push_back(temp);
                        }
                    }

                    if (i + 1 <= 4 && j - 1 >= 0) {
                        if (board[i + 1][j - 1] != 1 && board[i + 1][j - 1] != -1) {
                            Position end(i + 1, j - 1);
                            Move temp(start, end);
                            valid.push_back(temp);
                        }
                    }
                }
            }
        }
    }
    return valid;
}

vector<Position> ganh(int** board, Move m, int player) {
    vector<Position> result;
    
    int enemy = player * -1;
    
    int x = m.pos_end.x, y = m.pos_end.y;

    if (x - 1 >= 0 && x + 1 <= 4) {
        if (board[x - 1][y] == enemy && board[x + 1][y] == enemy) {
            Position temp1(x - 1, y), temp2(x + 1, y);
            result.push_back(temp1);
            result.push_back(temp2);
        }

        if (y - 1 >= 0 && y + 1 <= 4) {
            if (board[x + 1][y + 1] == enemy && board[x - 1][y - 1] == enemy) {
                Position temp1(x + 1, y + 1), temp2(x - 1, y - 1);
                result.push_back(temp1);
                result.push_back(temp2);
            }

            if (board[x + 1][y - 1] == enemy && board[x - 1][y + 1] == enemy) {
                Position temp1(x + 1, y - 1), temp2(x - 1, y + 1);
                result.push_back(temp1);
                result.push_back(temp2);
            }
        }
    }


    if (y - 1 >= 0 && y + 1 <= 4) {
        if (board[x][y - 1] == enemy && board[x][y + 1] == enemy) {
            Position temp1(x, y - 1), temp2(x, y + 1);
            result.push_back(temp1);
            result.push_back(temp2);
        }
    }
    return result;
}

vector<Position> adj(int** board, int** marked, Position pos, int player) {
    int x = pos.x, y = pos.y;

    vector<Position> res;

    if (x - 1 >= 0) {
        if (board[x - 1][y] == player && marked[x - 1][y] == 0) {
            Position t(x - 1, y);
            res.push_back(t);
        }
    }

    if (x + 1 <= 4) {
        if (board[x + 1][y] == player && marked[x + 1][y] == 0) {
            Position t(x + 1, y);
            res.push_back(t);
        }
    }

    if (y - 1 >= 0) {
        if (board[x][y - 1] == player && marked[x][y - 1] == 0) {
            Position t(x, y - 1);
            res.push_back(t);
        }
    }

    if (y + 1 <= 4) {
        if (board[x][y + 1] == player && marked[x][y + 1] == 0) {
            Position t(x, y + 1);
            res.push_back(t);
        }
    }

    if (x + 1 <= 4 && y + 1 <= 4) {
        if (board[x + 1][y + 1] == player && marked[x + 1][y + 1] == 0) {
            Position t(x + 1, y + 1);
            res.push_back(t);
        }
    }

    if (x - 1 >= 0 && y + 1 <= 4) {
        if (board[x - 1][y + 1] == player && marked[x - 1][y + 1] == 0) {
            Position t(x - 1, y + 1);
            res.push_back(t);
        }
    }

    if (x - 1 >= 0 && y - 1 >= 0) {
        if (board[x - 1][y - 1] == player && marked[x - 1][y - 1] == 0) {
            Position t(x - 1, y - 1);
            res.push_back(t);
        }
    }

    if (x + 1 <= 4 && y - 1 >= 0) {
        if (board[x + 1][y - 1] == player && marked[x + 1][y - 1] == 0) {
            Position t(x + 1, y - 1);
            res.push_back(t);
        }
    }


    return res;
}

bool check(int** board, Position pos) {
    int i = pos.x, j = pos.y;

    if (i - 1 >= 0) {
        if (board[i - 1][j] != 1 && board[i - 1][j] != -1) {
            return true;
        }
    }

    if (i + 1 <= 4) {
        if (board[i + 1][j] != 1 && board[i + 1][j] != -1) {
            return true;
        }
    }

    if (j - 1 >= 0) {
        if (board[i][j - 1] != 1 && board[i][j - 1] != -1) {
            return true;
        }
    }

    if (j + 1 <= 4) {
        if (board[i][j + 1] != 1 && board[i][j + 1] != -1) {
            return true;
        }
    }

    if ((i + j) % 2 == 0) {
        if (i + 1 <= 4 && j + 1 <= 4) {
            if (board[i + 1][j + 1] != 1 && board[i + 1][j + 1] != -1) {
                return true;
            }
        }

        if (i - 1 >= 0 && j + 1 <= 4) {
            if (board[i - 1][j + 1] != 1 && board[i - 1][j + 1] != -1) { 
                return true; 
            }
        }

        if (i - 1 >= 0 && j - 1 >= 0) {
            if (board[i - 1][j - 1] != 1 && board[i - 1][j - 1] != -1) {
                return true;
            }
        }

        if (i + 1 <= 4 && j - 1 >= 0) {
            if (board[i + 1][j - 1] != 1 && board[i + 1][j - 1] != -1) {
                return true;
            }
        }
    }


    return false;
}

bool chet(int** board, int** marked, Position pos) {
    marked[pos.x][pos.y] = 1;

    if (check(board, pos)) {
        return false;
    }

    int player = board[pos.x][pos.y];

    vector<Position> ke = adj(board, marked, pos, player);
    if (ke.size() == 0) {
        return true;
    }

    for (unsigned int i = 0; i < ke.size(); i++) {
        return chet(board, marked, ke.at(i));
    }

    return true;
}

int** init_marked() {
    int** marked = new int* [5];

    for (int i = 0; i < 5; i++) {
        marked[i] = new int[5];
        for (int j = 0; j < 5; j++) {
            marked[i][j] = 0;
        }
    }

    return marked;
}

void destroy_marked(int** marked) {
    for (int i = 0; i < 5; i++) {
        delete[] marked[i];
    }

    delete[] marked;
}

vector<Position> vay(int** board, Move m, int player) {
    int** new_board = copy_board(board);

    int enemy = player * -1;

    vector<Position> result;

    new_board[m.pos_start.x][m.pos_start.y] = 0;

    new_board[m.pos_end.x][m.pos_end.y] = player;

    vector<Position> ganh_move = ganh(board, m, player);

    for (unsigned int i = 0; i < ganh_move.size(); i++) {
        new_board[ganh_move.at(i).x][ganh_move.at(i).y] = player;
    }

    vector<Position> around;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (new_board[i][j] == enemy) {
                Position temp(i, j);
                around.push_back(temp);
            }
        }
    }

    for (unsigned int i = 0; i < around.size(); i++) {
        Position pos = around.at(i);
        int** sub_marked = init_marked();
        if (chet(new_board, sub_marked, pos)) {
            result.push_back(pos);
        }
        destroy_marked(sub_marked);
    }

    return result;
}

vector<Move> bay_or_mo(int** current_board, int** previous_board, int player) {
    vector<Move> result;

    int current = 0, previous = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (current_board[i][j] == 1) {
                current++;
            }
            else if (previous_board[i][j] == 1) {
                previous++;
            }
        }
    }

    if (current != previous) {
        return result;
    }

    Move move_temp = move_another(current_board, previous_board, player);

    vector<Position> around = Positionaround(move_temp.pos_start);

    for (unsigned int i = 0; i < around.size(); i++) {
        if (current_board[around[i].x][around[i].y] == player) {
            Move y(around[i], move_temp.pos_start);
            vector<Position> ganh_temp = ganh(current_board, y, player);
            if (ganh_temp.size() > 0) {
                result.push_back(y);
            }
        }
    }


    return result;
}

void act_move(int** board, Move m, int player) {
    vector<Position> ganh_move = ganh(board, m, player);

    vector<Position> vay_move = vay(board, m, player);

    for (int i = 0; i < ganh_move.size(); i++) {
        board[ganh_move.at(i).x][ganh_move.at(i).y] = player;
    }

    for (int i = 0; i < vay_move.size(); i++) {
        board[vay_move.at(i).x][vay_move.at(i).y] = player;
    }

    board[m.pos_start.x][m.pos_start.y] = 0;

    board[m.pos_end.x][m.pos_end.y] = player;

    cout << "-----------------------------------\n";
    print_board(board);
    system("pause");
}

Move select_move(int** current_board, int** previous_board, int player) {
    vector<Move> valid = get_valid_moves(current_board, previous_board, player);

    if (player == 1) {
        int max = -100, maxidx = 0;

        for (unsigned int i = 0; i < valid.size(); i++) {
            vector<Position> ganh_move = ganh(current_board, valid[i], 1);

            if (ganh_move.size() > 2) return valid[i];

            vector<Position> vay_move = vay(current_board, valid[i], 1);

            if (vay_move.size() > 2)return valid[i];

            int** current_board_temp = init_marked();

            int** previous_board_temp = init_marked();

            init(current_board_temp, current_board);

            init(previous_board_temp, previous_board);

            int score = minimax(current_board, previous_board, valid[i], -100, 100, 0, 1);

            init(current_board, current_board_temp);

            init(previous_board, previous_board_temp);

            if (score > max) {
                max = score;
                maxidx = i;
            }
        }

        return valid[maxidx];
    }


    else {
        int min = 100, minidx = 0;

        for (unsigned int i = 0; i < valid.size(); i++) {
            vector<Position> ganh_move = ganh(current_board, valid[i], -1);

            if (ganh_move.size() > 2)return valid[i];

            vector<Position> vay_move = vay(current_board, valid[i], -1);

            if (vay_move.size() > 2)return valid[i];

            int** current_board_temp = init_marked();

            int** previous_board_temp = init_marked();

            init(current_board_temp, current_board);

            init(previous_board_temp, previous_board);

            int score = minimax(current_board, previous_board, valid[i], -100, 100, 0, -1);

            init(current_board, current_board_temp);

            init(previous_board, previous_board_temp);

            if (score < min) {
                min = score;
                minidx = i;
            }
        }
        return valid[minidx];
    }
}

int minimax(int** current_board, int** previous_board, Move m, int alpha, int beta, int depth, int player) {
    bool check = endgame(current_board, m, player);

    if (check || depth == 0) {
        return score(current_board, m, player);
    }

    if (player == 1) {
        int bestscore = -20;

        vector<Move> valid = get_valid_moves(current_board, previous_board, -1);

        for (unsigned int i = 0; i < valid.size(); i++) {
            int x[5][5];

            static bool check = 0;

            static bool check_temp = 0;

            if (check == 0){
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++)
                        x[i][j] = current_board[i][j];
                check = 1;
            }

            int y[5][5];
            if (check_temp == 0) {
                for (int i = 0; i < 5; i++) 
                    for (int j = 0; j < 5; j++)
                        y[i][j] = previous_board[i][j];
                check_temp = 1;
            }

            act_move_another(current_board, previous_board, valid[i], -1);

            int score = minimax(current_board, previous_board, valid[i], alpha, beta, depth + 1, -1);

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    current_board[i][j] = x[i][j];
                }
                check = 0;
            }

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    previous_board[i][j] = y[i][j];
                }
                check_temp = 0;
            }

            bestscore = max(bestscore, score);

            alpha = max(alpha, bestscore);

            if (beta <= alpha) {
                break;
            }
        }

        return bestscore;
    }

    else {
        int bestscore = 20;

        vector<Move> valid = get_valid_moves(current_board, previous_board, 1);

        for (unsigned int i = 0; i < valid.size(); i++) {
            int x[5][5];
            static bool check = 0;
            static bool check_temp = 0;

            if (check == 0) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        x[i][j] = current_board[i][j];
                    }
                }
                check = 1;
            }

            int y[5][5];
            if (check_temp == 0) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        y[i][j] = previous_board[i][j];
                    }
                }
                check_temp = 1;
            }

            act_move_another(current_board, previous_board, valid[i], 1);

            int score = minimax(current_board, previous_board, valid[i], alpha, beta, depth + 1, 1);

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    current_board[i][j] = x[i][j];
                }
                check = 0;
            }

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    previous_board[i][j] = y[i][j];
                }
                check_temp = 0;
            }

            bestscore = min(bestscore, score);

            beta = min(beta, bestscore);

            if (beta <= alpha) {
                break;
            }
        }
        return bestscore;
    }
}

void init(int** board_1, int** board_2) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board_1[i][j] = board_2[i][j];
        }
    }
}

void act_move_another(int** board, int** previous_board, Move m, int player) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            previous_board[i][j] = board[i][j];
        }
    }

    vector<Position> ganh_move = ganh(board, m, player);

    vector<Position> vay_move = vay(board, m, player);

    board[m.pos_start.x][m.pos_start.y] = 0;
    board[m.pos_end.x][m.pos_end.y] = player;

    for (unsigned int i = 0; i < ganh_move.size(); i++) {
        board[ganh_move[i].x][ganh_move[i].y] = player;
    }

    for (unsigned int i = 0; i < vay_move.size(); i++) {
        board[vay_move[i].x][vay_move[i].y] = player;
    }
}

int score(int** board, Move m, int player) {
    int** sub_board = new int* [5];
    for (int i = 0; i < 5; i++) {
        sub_board[i] = new int[5];
    }

    init(sub_board, board);

    act_move(sub_board, m, player);

    int white = 0, black = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (sub_board[i][j] == 1) {
                white++;
            }
            if (sub_board[i][j] == -1) {
                black++;
            }
        }
    }
    return white - black;
}

bool endgame(int** board, Move m, int player) {
    return (abs(score(board, m, player)) == 16) ? 1 : 0;
}

vector<Position> Positionaround(Position x) {
    vector<Position> a;

    if ((x.x == 1 && (x.y == 1 || x.y == 3)) || x.x == 2 && x.y == 2 || (x.x == 3 && (x.y == 3 || x.y == 1))) {
        Position b[8];
        b[0].x = x.x - 1;
        b[0].y = x.y - 1;
        b[1].x = x.x - 1;
        b[1].y = x.y;
        b[2].x = x.x - 1;
        b[2].y = x.y + 1;
        b[3].x = x.x;
        b[3].y = x.y - 1;
        b[4].x = x.x;
        b[4].y = x.y + 1;
        b[5].x = x.x + 1;
        b[5].y = x.y - 1;
        b[6].x = x.x + 1;
        b[6].y = x.y;
        b[7].x = x.x + 1;
        b[7].y = x.y + 1;
        for (int i = 0; i < 8; i++)a.push_back(b[i]);
        return a;
    }

    if ((x.x == 2 && (x.y == 1 || x.y == 3)) || ((x.x == 1 || x.x == 3) && x.y == 2)) {
        Position b[4];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x + 1;
        b[1].y = x.y;
        b[2].x = x.x;
        b[2].y = x.y - 1;
        b[3].x = x.x;
        b[3].y = x.y + 1;
        for (int i = 0; i < 4; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 0 && x.y == 0) {
        Position b[3];
        b[0].x = x.x;
        b[0].y = x.y + 1;
        b[1].x = x.x + 1;
        b[1].y = x.y + 1;
        b[2].x = x.x + 1;
        b[2].y = x.y;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 0 && x.y == 4) {
        Position b[3];
        b[0].x = x.x;
        b[0].y = x.y - 1;
        b[1].x = x.x + 1;
        b[1].y = x.y - 1;
        b[2].x = x.x + 1;
        b[2].y = x.y;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 4 && x.y == 0) {
        Position b[3];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x - 1;
        b[1].y = x.y + 1;
        b[2].x = x.x;
        b[2].y = x.y + 1;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 4 && x.y == 4) {
        Position b[3];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x - 1;
        b[1].y = x.y - 1;
        b[2].x = x.x;
        b[2].y = x.y - 1;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 0 && (x.y == 1 || x.y == 3)) {
        Position b[3];
        b[0].x = x.x;
        b[0].y = x.y - 1;
        b[1].x = x.x;
        b[1].y = x.y + 1;
        b[2].x = x.x + 1;
        b[2].y = x.y;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 0 && x.y == 2) {
        Position b[5];
        b[0].x = x.x;
        b[0].y = x.y - 1;
        b[1].x = x.x;
        b[1].y = x.y + 1;
        b[2].x = x.x + 1;
        b[2].y = x.y - 1;
        b[3].x = x.x + 1;
        b[3].y = x.y;
        b[4].x = x.x + 1;
        b[4].y = x.y + 1;
        for (int i = 0; i < 5; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 4 && (x.y == 1 || x.y == 3)) {
        Position b[3];
        b[0].x = x.x;
        b[0].y = x.y - 1;
        b[1].x = x.x;
        b[1].y = x.y + 1;
        b[2].x = x.x - 1;
        b[2].y = x.y;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 4 && x.y == 2) {
        Position b[5];
        b[0].x = x.x;
        b[0].y = x.y - 1;
        b[1].x = x.x;
        b[1].y = x.y + 1;
        b[2].x = x.x - 1;
        b[2].y = x.y - 1;
        b[3].x = x.x - 1;
        b[3].y = x.y;
        b[4].x = x.x - 1;
        b[4].y = x.y + 1;
        for (int i = 0; i < 5; i++)a.push_back(b[i]);
        return a;
    }

    if ((x.x == 1 || x.x == 3) && x.y == 0) {
        Position b[3];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x + 1;
        b[1].y = x.y;
        b[2].x = x.x;
        b[2].y = x.y + 1;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 2 && x.y == 0) {
        Position b[5];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x + 1;
        b[1].y = x.y;
        b[2].x = x.x - 1;
        b[2].y = x.y + 1;
        b[3].x = x.x;
        b[3].y = x.y + 1;
        b[4].x = x.x + 1;
        b[4].y = x.y + 1;
        for (int i = 0; i < 5; i++)a.push_back(b[i]);
        return a;
    }

    if ((x.x == 1 || x.x == 3) && x.y == 4) {
        Position b[3];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x + 1;
        b[1].y = x.y;
        b[2].x = x.x;
        b[2].y = x.y - 1;
        for (int i = 0; i < 3; i++)a.push_back(b[i]);
        return a;
    }

    if (x.x == 2 && x.y == 4) {
        Position b[5];
        b[0].x = x.x - 1;
        b[0].y = x.y;
        b[1].x = x.x + 1;
        b[1].y = x.y;
        b[2].x = x.x - 1;
        b[2].y = x.y - 1;
        b[3].x = x.x;
        b[3].y = x.y - 1;
        b[4].x = x.x + 1;
        b[4].y = x.y - 1;
        for (int i = 0; i < 5; i++)a.push_back(b[i]);
        return a;
    }
    return a;
}

Move move_another(int** current_board, int** previous_board, int player) {
    Position start, end;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (previous_board[i][j] == current_board[i][j]) {
                continue;
            }
            else {
                if (previous_board[i][j] == -player) {
                    start.x = i; start.y = j;
                }
                else {
                    end.x = i; end.y = j;
                }
            }
        }
    }
    return Move(start, end);
}

void print_board(int** board, int** previous) {
    int l = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == -1) {
                cout << "X" << " ";
            }
            else if (board[i][j] == 1) {
                cout << "O" << " ";
            }
            else cout << "_" << " ";
            if (j == 4) {
                for (int l = 0; l < 5; l++) {
                    if (l == 0) {
                        cout << "       ";
                    }
                    if (previous[i][l] == -1) {
                        cout << "X" << " ";
                    }
                    else if (previous[i][l] == 1) {
                        cout << "O" << " ";
                    }
                    else cout << "_" << " ";
                }
            }
        }
        cout << endl;
    }
}

vector<Move> get_valid_moves(int** current_board, int** previous_board, int player) {
    vector<Move> a = bay_or_mo(current_board, previous_board, player);
    if (a.size() > 0)return a;
    vector<Move> h;
    vector<Position> b;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (current_board[i][j] == player) {
                Position x(i, j);
                b.push_back(x);
            }
        }
    }
    for (unsigned int i = 0; i < b.size(); i++) {
        vector<Position> c = Positionaround(b[i]);
        for (unsigned int j = 0; j < c.size(); j++) {
            if (current_board[c[j].x][c[j].y] == 0) {
                Move m(b[i], c[j]);
                h.push_back(m);
            }
        }
    }
    return h;
}






