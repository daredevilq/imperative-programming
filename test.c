#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

int stack[STACK_SIZE];
int top = 0;


#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out = 0, len = 0;


int cbuff_push(int cli_nr) {
	if (len>=CBUFF_SIZE)
	{
		return OVERFLOW;
	}
	else{
	cbuff[((len+out)%CBUFF_SIZE)]=cli_nr;
	len++;
	return OK;
	}

}

int cbuff_pop(void) {
	if (len==0)
	{
		return UNDERFLOW;
	}
	else{
	
	int temp;
	temp=out;
	out=((out+1)%CBUFF_SIZE);
	len--;
	return cbuff[temp];
	}
}

int cbuff_state(void) {
	return len;

}

void cbuff_print(void) {
	int i;
	i=out;
	int count;
	count=0;
	
	while (count<len)
	{
		printf("%d ",cbuff[i%CBUFF_SIZE]);
		
		i++;
		count++;
	}
	

}

int main()
{

	cbuff_push(1);
	cbuff_push(2);
	cbuff_pop();
	cbuff_pop();
	cbuff_print();


}