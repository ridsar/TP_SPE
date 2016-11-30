#include <stdio.h>
#include <stdlib.h>

/* You have to implement a function that can handle big value of the Fibonnacci
 * sequence. For that, instead of storing the value in a size_t, you'll use
 * array of char. Each cell will store one digit of the final value. The size
 * of the array is 1024 cells. You have to print the final value of the
 * sequence, without any zero before the value(10, not 00000...00010). 
 * Exemple:
 * To store 10 in a array of char str[1024], you have to put '0' into str[0]
 * and '1' in str[1]' 
 */

void print_fibo(char *str, size_t n) 
{
	size_t i = 0;
	while (i < n-1 && str[n-i-1] == 0)
		++i;
	for (; i < n; ++i)
	{
		printf("%d", str[n-i-1]);
	}
	printf("\n");
} 

void add_fibo(char *swap, char *f1, size_t n)
{
	int add, ret = 0;
	for (size_t i = 0; i < n; ++i)
	{
		add = swap[i] + f1[i] + ret;
		if (add >= 10)
		{
			ret = 1;
			f1[i] = add % 10;
		}
		else
		{
			ret = 0; 
			f1[i] = add;
		}
	}
}

void big_fibo(size_t n)
{
	char *f0 = calloc (1024 , sizeof(int));
	char *f1 = calloc (1024 , sizeof(int));
	f0[0] = 0;
	f1[0] = 1;
	if (n == 0)
		print_fibo(f0, 1024);
	else if (n == 1)	
		print_fibo(f1, 1024);
	else 
	{
		char *swap = malloc (1024 * sizeof(int));
		while (n >= 2)
		{
			for (size_t i = 0; i < 1024; ++i)
				swap[i] = f0[i];
			for (size_t j = 0; j < 1024; ++j)
				f0[j] = f1[j];
			add_fibo(swap, f1, 1024);
			--n;
		}
		print_fibo(f1, 1024);
		free(swap);
	}
	free(f0);
	free(f1);
}


/* You have to implement rotn function, that apply a rotation of n letter to
 * every alphanumeric character of str and print it. That mean that you replace
 * each letter/number by the n'th letter/number after, looping if necessary.
 * You have to handle negative rotation.
 * Exemple:
 *  rotn("abc09", -1) -> zab98
 */
void rotn(const char *str, int n)
{
	for (size_t i = 0; i < sizeof(str); ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			char c  = (char)(10+((str[i]-'0')+(n%10)))%10+'0';
			printf("%c", c);
		}
		if (str[i] >= 'a' && str[i] <= 'z')
		{	
			char c  = (char)(26+((str[i]-'a')+(n%26)))%26+'a';
			printf("%c", c);
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{	
			char c  = (char)(26+((str[i]-'A')+(n%26)))%26+'A';
			printf("%c", c);
		}
	}
}



#ifdef DEBUG

int main(void)
{
	for (size_t i = 0; i < 201; ++i)
		big_fibo(i); 
	rotn("abc09",-1);
	printf("\n");
	return 0;
}

#endif
