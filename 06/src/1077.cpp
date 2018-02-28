#include <iostream>
using namespace std;

class ScoreTree
{
    private:
        int size;
        int *inorder;
        int *output;
        int **output_mat;
        long **score_mat;
        int output_pos;

        bool getMin(int begin, int end, int &min_num, int &min_loc)
        {
            min_num = 101;
            bool flag = false;
            for(int i=begin; i<=end; ++i)
            {
                if(inorder[i]<min_num)
                {
                    min_num = inorder[i];
                    min_loc = i;
                    flag = true;
                }
            }
            return flag;
        }

        long getScore(int begin, int end)
        {
            if(end < begin)
                return 1;
            if(end == begin)
            {
                output[output_pos] = begin;
                ++output_pos;
                return inorder[begin];
            }
            int new_root, new_root_loc;
            getMin(begin, end, new_root, new_root_loc);
            output[output_pos] = new_root_loc;
            ++output_pos;
            return new_root
                +  getScore(begin, new_root_loc - 1)
                *  getScore(new_root_loc + 1, end);
        }

        long getMaxScore(int begin, int end)
        {
            if(end < begin)
                return 1;
            if(score_mat[begin][end])
                return score_mat[begin][end];
            if(end == begin)
            {
                //output[output_pos] = begin;
                //++output_pos;
                output_mat[begin][end] = begin;
                score_mat[begin][end] = inorder[begin];
                return inorder[begin];
            }

            long max_score = 0 ;
            long score;
            int max_score_loc;
            for(int i=begin; i<=end; ++i)
            {
                score = inorder[i]
                        +   getMaxScore(begin, i-1)
                        *   getMaxScore(i+1, end);
                if(max_score < score)
                {
                    max_score = score;
                    max_score_loc = i;
                }
            }
            output_mat[begin][end] = max_score_loc;
            score_mat[begin][end] = max_score;
            return max_score;
        }

        void getMaxScorePos(int begin, int end)
        {
            if(end < begin)
                return;
            if(end == begin)
            {
                output[output_pos] = begin;
                ++output_pos;
                return; 
            }
            output[output_pos] = output_mat[begin][end];
            ++output_pos;
            getMaxScorePos(begin, output_mat[begin][end] - 1);
            getMaxScorePos(output_mat[begin][end] + 1, end);
        }
    public:
        void input()
        {
            cin >> size;
            inorder = new int [size + 1];
            output = new int [size + 1];
            output_mat = new int* [size + 1];
            score_mat = new long* [size + 1];
            for(int i=1; i<=size; ++i)
            {
                output_mat[i] = new int [size + 1];
                score_mat[i] = new long [size + 1];
            }
            output_pos = 1;
            for(int i=1; i<=size; ++i)
            {
                for(int j=1; j<=size; ++j)
                    score_mat[i][j] = 0;
            }

            for(int i=1; i<=size; ++i)
                cin >> inorder[i];
        }

        void print()
        {
            cout << getMaxScore(1, size) << endl;
            getMaxScorePos(1, size);
            cout << output[1];
            for(int i=2; i<=size; ++i)
                cout << " " << output[i];
            cout << endl;
            /*
            for(int i=1; i<=size; ++i)
            {
                for(int j=1; j<=size; ++j)
                    cout << output_mat[i][j];
                cout << endl;
            }
            */
        }

};

int main(void)
{
    ScoreTree score_tree;
    score_tree.input();
    score_tree.print();

    return 0;
}
