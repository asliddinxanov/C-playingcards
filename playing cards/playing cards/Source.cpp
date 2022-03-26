#include<stdio.h>
#include<string.h>
#define MARK_WEIGHT 13
#define NUMBER_OF_CARDS (13 * 4)

char mark[] = "DHCS";
char number[] = "A23456789XJQK";
int GetIndex(char table[], char ch)
{
	int i = 0;
	while (table[i] != '\0') {
		if (table[i] == ch) //�P (mark�Ƀ}�[�N�̒ʂ��ԍ�0�`3�Cnubmer�ɐ����̒ʂ��ԍ�0�`12�����)
			break;
		i++;
	}
	return(table[i] == '\0') ? -1 : i;//�Q�@((����)? YES:NO�̏�������)
}
int CardToValue(char card[]) {
	int iMark, iNumber;
	iMark = GetIndex(mark, card[0]);
	iNumber = GetIndex(number, card[1]);
	return iMark * MARK_WEIGHT + iNumber;//�R�@(�_�C��0�`�X�y�[�h3�AA0�`K12��g�ݍ��킹�Ĉ�̐����Ńh�����v��\��)
}
void ValueToCard(int value, char card[]) {
	card[0] = mark[value / MARK_WEIGHT];
	card[1] = number[value % MARK_WEIGHT];//4�@(�������]�肪�O�Ȃ�_�C���Ȃ�)
	card[2] = '0';
}
void SortValue(int value[], int left, int right) {
	int i, j, pv, step;

	if (right - left >= 1) {
		pv = value[left];
		i = left;
		j = right;
		step = 1;
		while (i < j) {
			if (step == 1) {
				if (value[j] < pv) {
					value[i++] = value[j];
					step = 2;
				}
				else
					j--;
			}
			else {
				if (value[i] >= pv) {
					value[j--] = value[i];
					step = 1;
				}
				else
					i++;
			}
		}
		value[j] = pv;
		SortValue(value, left, j - 1);
		SortValue(value, j + 1, right);
	}
}
void SortCards(char cards[][3]) {
	int i, value[NUMBER_OF_CARDS];
	for (i = 0;i < NUMBER_OF_CARDS;i++)
		value[i] = CardToValue(cards[i]);
	SortValue(value, 0, NUMBER_OF_CARDS - 1);
	for (i = 0;i < NUMBER_OF_CARDS;i++)
		ValueToCard(value[i], cards[i]);
}
void PrintCards(char cards[][3]) {
	for (int i = 0;i < NUMBER_OF_CARDS;i++) {
		printf(" %c %c ", cards[i][0], cards[i][1]);//�T
	}
	printf("\n");
}
int main(void) {

	char cards[NUMBER_OF_CARDS][3] = {//�U
	{"SA"},{"S2"},{"S8"},{"S4"},{"S5"},{"S6"},{"S7"},{"S3"},{"S9"},{"SX"},{"SJ"},{"SQ"},{"SK"},
	{"DA"},{"D3"},{"D2"},{"D4"},{"D5"},{"D6"},{"D7"},{"D8"},{"D9"},{"DX"},{"DJ"},{"DQ"},{"DK"},
	{"HA"},{"HK"},{"H3"},{"H4"},{"H5"},{"HX"},{"H7"},{"H8"},{"H9"},{"H6"},{"HJ"},{"HQ"},{"H2"},
	{"CA"},{"CQ"},{"C3"},{"C4"},{"C5"},{"C6"},{"C7"},{"C9"},{"C8"},{"CX"},{"CJ"},{"C2"},{"CK"}
	};
	printf("�����J�[�h\n");
	PrintCards(cards);
	SortCards(cards);
	printf("---------------------------\n");
	printf("�\�[�g��J�[�h\n");
	PrintCards(cards);
	return 0;
}