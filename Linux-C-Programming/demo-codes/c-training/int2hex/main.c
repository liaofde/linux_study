#include <stdio.h>

int main(void)
{
	int num = 0;
	int div = 0;
	int rest = 0;
	char c[16] = "0123456789ABCDEF";
	char str[100];
	int i = 0;
	int len = 0;
	char tmp;

	printf("hello, bin2hex demo \n");

	scanf("%d", &num);
	printf("num = %d :0x%x \n", num, num);

	div = num;
	i = 0;
	while(div != 0)
	{
		rest = div % 16;
		div = div / 16;

		printf("rest = %c\n", c[rest]);
		str[i] = c[rest];
		i++;
	}
	str[i] = '\0';
	printf("str = %s \n", str);

	len = i;
	printf("len = %d \n", len);
	/* reverse string , like "hello" -> "olleh" */	
	for(i = 0; i < len/2; i++)
	{
		tmp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = tmp;
	}
	printf("reverse str = %s \n", str);


/*
	if(rest < 10)
		printf("rest = %c", rest+'0');
	else
		printf("rest = %c", rest-10+'A');
*/
	//printf("div = %c\n", c[div]);

	return 0;
}
