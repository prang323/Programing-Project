#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void yahtzee_description() {

    printf("\n=====================================================\n");
    printf("               YAHTZEE 게임 설명\n");
    printf("=====================================================\n\n");

    printf("Yahtzee는 5개의 주사위를 최대 3번 굴려\n");
    printf("족보(카테고리)에 점수를 기록해 총점을 겨루는 게임입니다.\n\n");

    printf("1) 5개의 주사위를 굴린 뒤, 원하는 주사위들을 골라 최대 2번 다시 굴리기 가능.\n");
    printf("2) 최종 주사위를 보고 아래 족보 중 하나를 선택해 점수 기록.\n");
    printf("3) 13개의 족보를 모두 채우면 점수 집계 후 게임 종료.\n\n");

    printf("=====================================================\n");
    printf("                  족보 설명표\n");
    printf("=====================================================\n");

    printf("+----------------------+----------------------------+\n");
    printf("|         족보         |            설명            |\n");
    printf("+----------------------+----------------------------+\n");
    printf("| 1 (Ones)             | 1의 합계                   |\n");
    printf("| 2 (Twos)             | 2의 합계                   |\n");
    printf("| 3 (Threes)           | 3의 합계                   |\n");
    printf("| 4 (Fours)            | 4의 합계                   |\n");
    printf("| 5 (Fives)            | 5의 합계                   |\n");
    printf("| 6 (Sixes)            | 6의 합계                   |\n");
    printf("+----------------------+----------------------------+\n");
    printf("| Bonus                | 상단 점수 합계 ≥ 63 → 35점 |\n");
    printf("+----------------------+----------------------------+\n");
    printf("| Three of a Kind      | 같은 숫자 3개 → 주사위 합  |\n");
    printf("| Four of a Kind       | 같은 숫자 4개 → 주사위 합  |\n");
    printf("| Full House           | 3개 + 2개 → 25점           |\n");
    printf("| Small Straight       | 연속된 숫자 4개 → 30점     |\n");
    printf("| Large Straight       | 연속된 숫자 5개 → 40점     |\n");
    printf("| Yahtzee              | 모두 동일 → 50점           |\n");
    printf("+----------------------+----------------------------+\n");
    printf("| Chance               | 모든 주사위 합             |\n");
    printf("+----------------------+----------------------------+\n\n");

}

void print_dice(int dice[5],int reroll_count) {
    printf("\n===== %d번째 주사위 결과 =====\n", reroll_count+1);
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

void reroll_dice(int dice[5]) {
    int reroll_count=0;

    while (reroll_count < 2) {
        int reroll_answer = -1;
        printf("\n다시 굴릴 주사위 번호를 입력하세요(ex : 1 3 4)(없다면 0) : ");

        while (scanf_s("%d", &reroll_answer) == 1) {
            if (reroll_answer == 0) {
                break;
            }
            if (reroll_answer < 1 || reroll_answer > 5) {
                printf("\n1~5만 입력하거나 0을 입력하세요 : ");
                continue;
            }
            dice[reroll_answer - 1] = rand() % 6 + 1;

            int c = getchar();
            if (c == '\n' || c == EOF) {
                break;
            }
        }

        if (reroll_answer == -1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (reroll_answer == 0) {
            break;
        }

        reroll_count++;
        print_dice(dice, reroll_count);
    }
}

int main() {
    int start;
    int dice[5];
    int score[13];
    int used[13];

    for (int i = 0; i < 13; i++) {
        score[i] = 0;
        used[i] = 0;
    }

    srand((unsigned int)time(NULL));

    printf("====== YAHTZEE ======\n\n");
    printf("1. 게임 시작하기\n");
    printf("2. 게임 설명 보기\n\n");
    printf("원하는 번호를 입력하세요. : ");

    while (1) {
        start = -1;
        start = getchar();

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (start == '1') {
            break;
        }
        else if (start == '2') {
            yahtzee_description();
            break;
        }
        else {
            printf("다시 입력하여 주세요: ");
        }
    }

    printf("\n\n\n====== YAHTZEE 게임을 시작합니다! ======\n");

    for (int turn = 1; turn <= 13; turn++) {
        printf("\n\n====== %d / 13 턴 ======\n", turn);

        for (int i = 0; i < 5; i++) {
            dice[i] = rand() % 6 + 1;
        }

        print_dice(dice, 0);
        reroll_dice(dice);

        printf("\n최종 주사위: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", dice[i]);
        }
    }
}