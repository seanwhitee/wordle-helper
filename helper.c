#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *word, *history; // File stream pointer
void read_words_data(char wordsStore[][6], int words_data_length);
void read_history_data(char historyStore[][6], int history_data_length);
void delet_function(char board[][6], char result[], char ans[], int board_length);
void board_beautiful_view(char board[][6], int board_length);
int main()
{
    int guess_count = 0; // user guess times

    // Read file
    word = fopen("words.txt", "r");
    history = fopen("history.txt", "r");
    int words_data_length = 2315;
    int history_data_length = 270;
    char wordsStore[2316][6];
    char historyStore[271][6];
    // File can't be opened
    if (word == NULL || history == NULL)
    {
        printf("Files can't be opened!\n");
    }
    // File are opened
    else
    {
        // store data into array call *store[]
        read_words_data(wordsStore, words_data_length);
        read_history_data(historyStore, history_data_length);

        // delet words in history.txt
        for (int i = 0; i < history_data_length; i++)
        {
            for (int j = 0; j < words_data_length; j++)
            {
                if (strcmp(wordsStore[j], historyStore[i]) == 0)
                {
                    strcpy(wordsStore[j], " ");
                }
            }
        }

        // copy all remain words to new array call board
        char board[2046][6];
        int position = 0;
        for (int i = 0; i < words_data_length; i++)
        {
            if (strcmp(wordsStore[i], " ") != 0)
            {
                strcpy(board[position++], wordsStore[i]);
            }
        }

        for (int i = 0; i < position; i++)
        {
            printf("%s%s", board[i], (i + 1) % 10 ? " " : "\n");
        }
        puts("");
        // close
        fclose(word);
        fclose(history);
        // user sets answer
        char ans[6];
        printf("Please input your guessing when playing wordle: ");
        scanf("%s", ans);

        // user sets result
        char result[6] = "bbbbb"; // result initialization
        printf("Please input your guessing result when playing wordle\n");
        printf("'g' for green, 'y' for yellow, 'b' for black (ex: ggggg): ");
        scanf("%s", result);
        puts("");

        // if input "ggggg", end program
        while (strcmp(result, "ggggg") != 0)
        {
            // delet the incorrect words in board
            delet_function(board, result, ans, position);

            // make view of board more beautiful
            board_beautiful_view(board, position);

            puts("");
            printf("\n");
            // printf("\n");
            // user sets answer
            printf("Please input your guessing when playing wordle: ");
            scanf("%s", ans);

            // user sets result
            printf("Please input your guessing result when playing wordle\n");
            printf("'g' for green, 'y' for yellow, 'b' for black (ex: ggggg): ");
            scanf("%s", result);

            puts("");
        } // end of while
    }
} // end of main
void board_beautiful_view(char board[][6], int board_length)
{

    char new[2046][6];
    int position = 0;
    for (int i = 0; i < board_length; i++)
    {
        if (strcmp(board[i], " ") != 0)
        {
            strcpy(new[position], board[i]);
            position++;
        }
    }

    // print new board
    for (int i = 0; i < position; i++)
    {
        printf("%s%s", new[i], (i + 1) % 10 ? " " : "\n");
    }
}
void read_words_data(char store[][6], int data_length)
{
    rewind(word);
    char temp[100];
    for (int i = 0; i < data_length; i++)
    {
        if (fscanf(word, "%s", temp) != EOF)
        {
            strcpy(store[i], temp);
        }
    }
}
void read_history_data(char store[][6], int data_length)
{
    char dates[100], days[100], answer[100];

    // move file pointer to second line data in file "history.txt"
    fseek(history, 17, SEEK_SET);
    for (int i = 0; i < data_length; i++)
    {
        if (fscanf(history, "%s %s %s", dates, days, answer) != EOF)
        {
            for (int pass = 0; pass < 5; pass++)
            {
                if (isalpha(answer[pass]) && isupper(answer[pass]))
                {
                    answer[pass] = tolower(answer[pass]);
                }
            }
            strcpy(store[i], answer);
        }
    }
}
void delet_function(char board[][6], char result[], char ans[], int board_length)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < board_length; j++)
        {
            // delet words in board which has same charactor and position with feeback 'g'
            if (result[i] == 'g' && board[j][i] != ans[i])
            {
                strcpy(board[j], " ");
            }
            else if (result[i] == 'y')
            {
                // feeback is 'y', and words have such alphabet but on wrong place
                if (board[j][i] == ans[i])
                {
                    strcpy(board[j], " ");
                }
                // feeback is 'y', but words don't have such that alphabet, and delet those words
                int flag = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (i != k && board[j][k] == ans[i])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    strcpy(board[j], " ");
                }
            }

            else if (result[i] == 'b')
            {

                int ok = 1;
                for (int pass = 0; pass < 5; pass++)
                { // pass every charactor in every words
                    if ((result[pass] == 'y' || result[pass] == 'g') && ans[pass] == ans[i])
                    {
                        ok = 0;
                        break;
                    }
                }
                if (!ok)
                {
                    break;
                }
                else if (ok)
                {
                    for (int l = 0; l < 5; l++)
                    {
                        if (board[j][l] == ans[i])
                        {
                            strcpy(board[j], " ");
                        }
                    }
                }
            }
        }
    }
}