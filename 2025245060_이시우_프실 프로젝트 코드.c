#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void yahtzee_description() {
    printf("\n================================================================\n");
    printf("               YAHTZEE 게임 설명\n");
    printf("================================================================\n\n");

    printf("Yahtzee는 5개의 주사위를 최대 3번 굴려\n");
    printf("족보(카테고리)에 점수를 기록해 총점을 겨루는 게임입니다.\n\n");

    printf("1) 5개의 주사위를 굴린 뒤, 원하는 주사위들을 골라 최대 2번 다시 굴리기 가능.\n");
    printf("2) 최종 주사위를 보고 아래 족보 중 하나를 선택해 점수 기록.\n");
    printf("3) 13개의 족보를 모두 채우면 점수 집계 후 게임 종료.\n\n");

    printf("================================================================\n");
    printf("                           족보 설명표\n");
    printf("================================================================\n");

    printf("+----------------------+---------------------------------------+\n");
    printf("|         족보         |                  설명                 |\n");
    printf("+----------------------+---------------------------------------+\n");
    printf("| 1 (Ones)             | 1들의 합만큼의 점수                   |\n");
    printf("| 2 (Twos)             | 2들의 합만큼의 점수                   |\n");
    printf("| 3 (Threes)           | 3들의 합만큼의 점수                   |\n");
    printf("| 4 (Fours)            | 4들의 합만큼의 점수                   |\n");
    printf("| 5 (Fives)            | 5들의 합만큼의 점수                   |\n");
    printf("| 6 (Sixes)            | 6들의 합만큼의 점수                   |\n");
    printf("+----------------------+---------------------------------------+\n");
    printf("| Bonus                | 상단 점수 합계 ≥ 63 → 35점            |\n");
    printf("+----------------------+---------------------------------------+\n");
    printf("| Three of a Kind      | 같은 숫자 3개 → 주사위 합만큼의 점수  |\n");
    printf("| Four of a Kind       | 같은 숫자 4개 → 주사위 합만큼의 점수  |\n");
    printf("| Full House           | 같은 숫자 (3개 + 2개) → 25점          |\n");
    printf("| Small Straight       | 연속된 숫자 4개 → 30점                |\n");
    printf("| Large Straight       | 연속된 숫자 5개 → 40점                |\n");
    printf("| Yahtzee              | 숫자가 모두 동일 → 50점               |\n");
    printf("+----------------------+---------------------------------------+\n");
    printf("| Chance               | 모든 주사위 합                        |\n");
    printf("+----------------------+---------------------------------------+\n\n");
}

int solo_number(int dice[5], int number) {  //1~6 계산
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == number) {
            sum += number;
        }
    }
    return sum;
}

int three_of_kind(int dice[5]) {    //쓰리카드 계산
    int x[6] = {0};
    for (int i = 0; i < 5; i++) {
        x[dice[i]-1]++;
    }
    for (int i = 0; i < 6; i++) {
        if (x[i] >= 3) {
            return chance(dice);
        }
    }
    return 0;
}

int four_of_kind(int dice[5]) {     //포카드 계산
    int x[6] = {0};
    for (int i = 0; i < 5; i++) {
        x[dice[i]-1]++;
    }
    for (int i = 0; i < 6; i++) {
        if (x[i] >= 4) {
            return chance(dice);
        }
    }
    return 0;
}

int full_house(int dice[5]) {       //풀하우스 계산
    int x[6] = {0};
    for (int i = 0; i < 5; i++) {
        x[dice[i]-1]++;
    }
    int three_same = 0, two_same = 0;
    for (int i = 0; i < 6; i++) {
        if (x[i] == 3) three_same = 1;
        if (x[i] == 2) two_same = 1;
    }
    if (three_same && two_same)
        return 25;
    else
        return 0;
}

int small_straight(int dice[5]) {       //스몰스트레이트 계산
    int x[6] = {0};
    for (int i = 0; i < 5; i++) {
        x[dice[i] - 1] = 1;
    }
    if ((x[0] && x[1] && x[2] && x[3]) == 1 ||
        (x[1] && x[2] && x[3] && x[4]) == 1 ||
        (x[2] && x[3] && x[4] && x[5]) == 1) {
        return 30;
    }
    return 0;
}

int large_straight(int dice[5]) {       //라지스트레이트 계산
    int x[6] = {0};
    for (int i = 0; i < 5; i++) {
        x[dice[i] - 1] = 1;
    }
    if ((x[0] && x[1] && x[2] && x[3] && x[4]) == 1 ||
        (x[1] && x[2] && x[3] && x[4] && x[5]) == 1) {
        return 40;
    }
    return 0;
}

int yahtzee(int dice[5]) {          //야찌 계산
    for (int i = 1; i < 5; i++) {
        if (dice[i] != dice[0]) {
            return 0;
        }
    }
    return 50;
}

int chance(int dice[5]) {       //찬스 계산
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += dice[i];
    }
    return sum;
}

int final_score(int dice[5], int which) {        //점수 계산 함수
    if (which >= 1 && which <= 6) {
        return solo_number(dice, which);
    }
    switch (which) {
    case 7: return three_of_kind(dice);
    case 8: return four_of_kind(dice);
    case 9: return full_house(dice);
    case 10: return small_straight(dice);
    case 11: return large_straight(dice);
    case 12: return yahtzee(dice);
    case 13: return chance(dice);
    default: return 0;
    }
}

void print_scorecard(int score[13], int used[13], int dice[5]) {    //게임 중 점수 기록표 출력 함수
    printf("\n===============================================\n");
    printf("                  점수 기록표\n");
    printf("===============================================\n");

    char category[13][18] = {
        "1. Ones          ", "2. Twos          ", "3. Threes        ",
        "4. Fours         ", "5. Fives         ", "6. Sixes         ",
        "7. 3 of a Kind   ", "8. 4 of a Kind   ", "9. Full House    ",
        "10. Sm Straight  ", "11. Lg Straight  ", "12. Yahtzee      ",
        "13. Chance       "
    };

    
    int up_score = 0;                           // 상단 점수 합계 계산
    for (int i = 0; i < 6; i++) {
        if (used[i]) {
            up_score += score[i];
        }
    }

    for (int i = 0; i < 6; i++) {               // 상단 족보 출력
        printf("| %s | ", category[i]);
        if (used[i]) { //이미 기록했는가?
            printf("%3d점  |\n", score[i]);
        }
        else {
            int potential = solo_number(dice, i + 1);
            printf("(%2d점) |\n", potential);
        }
    }

    printf("+----------------------------------------------\n");    //보너스 출력
    if (up_score >= 63) {
        printf("| Bonus (상단 합계 >= 63점)  | 35점\n");
    }
    else {
        printf("| Bonus (상단 합계 >= 63점)  | 0점\n");
    }
    printf("+----------------------------------------------\n");

    for (int i = 6; i < 13; i++) {              // 하단 족보 출력
        printf("| %s | ", category[i]);
        if (used[i]) { //이미 기록했는가?
            printf("%3d점  |\n", score[i]);
        }
        else {
            int potential = final_score(dice, i + 1);
            printf("(%2d점) |\n", potential);
        }
    }

    printf("===============================================\n\n");
}

void print_dice(int dice[5], int reroll_count) {    //주사위 결과 출력 함수
    printf("\n====== %2d번째 주사위 결과 =========================================================\n", reroll_count + 1);
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

void reroll_dice(int dice[5], int score[13], int used[13]) {    //주사위 리롤 함수
    int reroll_count = 0;

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
        if (reroll_count == 1) {
            print_dice(dice, reroll_count);
            print_scorecard(score, used, dice);
        }
    }
    printf("\n====== 최종 주사위 결과 ===========================================================\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
    print_scorecard(score, used, dice);
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

    printf("========== YAHTZEE ==========\n\n");
    while (1) {
        printf("1. 게임 시작하기\n");
        printf("2. 게임 설명 보기\n\n");
        printf("원하는 번호를 입력하세요. : ");

        start = getchar();

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (start == '1') {
            break;
        }
        else if (start == '2') {
            yahtzee_description();
            continue;
        }
        else {
            printf("다시 입력하여 주세요: ");
        }
    }

    printf("\n\n\n====== YAHTZEE 게임을 시작합니다! ======\n");

    for (int turn = 1; turn <= 13; turn++) {
        printf("\n\n\n====== %2d / 13 턴 =================================================================\n", turn);

        for (int i = 0; i < 5; i++) {
            dice[i] = rand() % 6 + 1;
        }

        print_dice(dice, 0);
        print_scorecard(score, used, dice);
        reroll_dice(dice, score, used);

        // 족보 선택 및 점수 기록
        int choice;
        while (1) {
            printf("\n점수를 기록할 족보 번호를 선택하세요 (1~13): ");
            if (scanf_s("%d", &choice) != 1) {
                while (getchar() != '\n');
                printf("\n잘못된 입력입니다. 다시 입력하세요.\n");
                continue;
            }
            while (getchar() != '\n');

            if (choice < 1 || choice > 13) {
                printf("\n1~13 사이의 숫자를 입력하세요.\n");
                continue;
            }

            if (used[choice - 1]) {
                printf("\n이미 기록된 족보입니다. 다른 족보를 선택하세요.\n");
                continue;
            }

            break;
        }

        // 선택한 족보에 점수 기록
        score[choice - 1] = final_score(dice, choice);
        used[choice - 1] = 1;
    }

    // 게임 종료 후 최종 점수 집계
    printf("\n====== 게임 종료! ==============================================================\n");                        
    int upper_sum = 0;
    for (int i = 0; i < 6; i++) {
        upper_sum += score[i];
    }

    int bonus; 
    if (upper_sum >= 63) {
        bonus = 35;
    }
    else {
        bonus = 0;
    }

    int total = upper_sum + bonus;
    for (int i = 6; i < 13; i++) {
        total += score[i];
    }

    print_scorecard(score, used, dice);
    printf("상단 점수 합계: %d점\n", upper_sum);
    printf("보너스: %d점\n", bonus);
    printf("총점: %d점", total);

    return 0;
}
