#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static inline int getn(int x)
{
	return (x < 5) ? x : x - 1;
}

//从个位数开始，每次插入一个数字，计算有效的排列总数
static int get_total(int x)
{
	int c, n, an;
	int an_1 = 1;
	int an_2 = 0;
	int cr = x % 10;
	int count = getn(cr);
	int count_1 = count;
	int count_2 = 0;
	x /= 10;
	while (x > 0) {
		c = x % 10;
		n = getn(c);
		an = 9 * an_1 - an_2;	//10, 100, 1000...的全排列
		switch (c) {
		case 5:
			//5后面的数字是无效数字，重新计算
			count = 5 * an - 1;
			break;
		case 8:
			//84以下的位可任取，总数为an_1
			if (cr > 4) 
				count += an * n - an_1;
			//84以下的位不能任取，总是为count_2（不含0）
			else if (cr == 4)
				count += an * n - count_2 - 1;
			//cr小于4的情况，直接插入
			else
				count += an * n;
			break;
		case 9:
			count += an * n - an_1;
			break;
		default:
			count += an * n;
		}
		an_2 = an_1;
		an_1 = an;
		cr = c;
		count_2 = count_1;
		count_1 = count;
		x /= 10;
	}
	return count;
}
	
int main(int argc, char **argv)
{
	int min = 0;
	int max = 0;
	/*
	if (scanf("%d %d", &min, &max) <= 0) {
		fprintf(stderr, "Error Input\n");
		return 1;
	}
	*/
	min = 1;
	max = INT_MAX;

	int count_min = get_total(min - 1);
	int count_max = get_total(max);

	printf("%d\n", count_max - count_min);
	return 0;
}

