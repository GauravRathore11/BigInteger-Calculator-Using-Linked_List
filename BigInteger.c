#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"BigInteger.h"

// typedef struct node
// {
//     int data;
//     struct node *next;
// }node;
// struct BigInteger{
//     node*head;
//     int length;
// };
node *newnode()
{
    node *temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    return temp;
}
void display(struct BigInteger s1)
{
    while (s1.head)
    {
        printf("%d", s1.head->data);
        s1.head = s1.head->next;
    }
    printf("\n");
}
struct BigInteger initialize(char *str)
{
    int i = 0,length=0;
    struct BigInteger s1;
    s1.head = NULL;
    // if(str[0]=='-'){
    //     s1.sign='-';
    //     i++;
    //     length++;
    // }
    // s1.sign='+';
    while (str[i] != '\0')
    {
        node *temp = newnode();
        temp->data = str[i] - 48;
        temp->next = s1.head;
        s1.head = temp;
        i++;
        length++;
    }
    // head=head->next;
    s1.length=length;
    // display(s1);
    return s1;
}
//ADDITION
struct BigInteger add(struct BigInteger n1,struct BigInteger n2)
{
    // node *n1 = convertToLinkList(a);
    // node *n2 = convertToLinkList(b);
    struct BigInteger res;
    res.head=NULL;
    // res.sign='+';
    int carry = 0, sum = 0;
    while (n1.head && n2.head)
    {
        node *temp = newnode();
        sum = (n1.head->data + n2.head->data + carry) % 10;
        temp->data = sum;
        carry = (n1.head->data + n2.head->data + carry) / 10;
        temp->next = res.head;
        res.head = temp;
        n1.head = n1.head->next;
        n2.head = n2.head->next;
    }
    while (n1.head)
    {
        node *temp = newnode();
        sum = (n1.head->data + carry) % 10;
        temp->data = sum;
        temp->next = res.head;
        res.head = temp;
        carry = (n1.head->data + carry) / 10;
        n1.head = n1.head->next;
    }
    while (n2.head)
    {
        node *temp = newnode();
        sum = (n2.head->data + carry) % 10;
        temp->data = sum;
        temp->next = res.head;
        res.head = temp;
        carry = (n2.head->data + carry) / 10;
        n2.head = n2.head->next;
    }
    if (carry > 0)
    {
        node *temp = newnode();
        temp->data = carry;
        temp->next = res.head;
        res.head = temp;
    }

    return res;
}
//REVERSE
void reverse(struct BigInteger *num1){
    if(!(num1->head)||!(num1->head->next)){
        return;
    }
    node*p1=num1->head,*p2=num1->head->next,*p3=num1->head->next->next;
    while(p2!=NULL){
        if(p2->next==NULL){
            p2->next=p1;
            num1->head->next=NULL;
            num1->head=p2;
            break;
        }
        p2->next=p1;
        p1=p2;
        p2=p3;
        p3=p3->next;
    }
}
int compare(struct BigInteger s1,struct BigInteger s2){
    int len1=s1.length,len2=s2.length;
    if(len1>len2) return 1;
    else if(len2>len1) return 2;
    else{
        reverse(&s1);
        reverse(&s2);

        //case when length of both strings is same now we need to check which number is greater
        for(int i=0;i<len1;i++){
            if(s1.head->data>s2.head->data) {
            reverse(&s1);
            reverse(&s2);
            return 1;
            }
            else if(s1.head->data<s2.head->data){
            reverse(&s1);
            reverse(&s2);
            return 2;
            }
        }
    }
    reverse(&s1);
    reverse(&s2);
    //if we have not return yet then both numbers are equal
    return 0;
}
void borrow(node*head){
    if(!head)
    return;
    else if(head->data>0){
        head->data--;
        return;
    }
    else{
        borrow(head->next);
        head->data=9;
    }
    
}
struct BigInteger sub(struct BigInteger n1,struct BigInteger n2){
    struct BigInteger res;
    int minus=0;
    res.head=NULL;
    // res.sign='+';
    int k=compare(n1,n2);
    // printf("\nk=%d\n",k);
    if(k==0){
        node*temp=(node*)malloc(sizeof(node*));
        temp->next=NULL;
        temp->data=0;
        res.head=temp;
        return res;
    }
    if(k==2){
        minus=1;
        struct BigInteger t;
        t=n1;
        n1=n2;
        n2=t;
    }
    while(n1.head&&n2.head){
        node*temp=newnode();
        if(n1.head->data<n2.head->data){
            borrow(n1.head->next);
            n1.head->data+=10;
        }
        temp->data=n1.head->data-n2.head->data;
        temp->next=res.head;
        res.head=temp;
        n1.head=n1.head->next;
        n2.head=n2.head->next;
    }
    while(n1.head){
        node*temp=newnode();
        temp->data=n1.head->data;
        temp->next=res.head;
        res.head=temp;
        n1.head=n1.head->next;
    }
    while(res.head->data==0){
        node*temp=res.head;
        res.head=res.head->next;
        free(temp);
    }
    if(minus==1){
        res.head->data=-(res.head->data);
    }
    return res;
}
void insertAtHead(struct node**head,int val){
    node*temp=newnode();
    temp->data=val;
    temp->next=*head;
    *head=temp;
}
node* addMul(node*num1,node*num2,int itr){
    node*res=NULL;
    for(int i=0;i<itr;i++){
        node*temp=newnode();
        temp->data=num2->data;
        num2=num2->next;
        if(!res) res=temp;
        else{
            temp->next=res;
            res=temp;
        }
    }
    int carry=0;
    int sum=0;
    while (num1 && num2)
    {
        node *temp = newnode();
        sum = (num1->data + num2->data + carry) % 10;
        temp->data = sum;
        carry = (num1->data + num2->data + carry) / 10;
        temp->next = res;
        res = temp;
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1)
    {
        node *temp = newnode();
        sum = (num1->data + carry) % 10;
        temp->data = sum;
        temp->next = res;
        res = temp;
        carry = (num1->data + carry) / 10;
        num1 = num1->next;
    }
    while (num2)
    {
        node *temp = newnode();
        sum = (num2->data + carry) % 10;
        temp->data = sum;
        temp->next = res;
        res = temp;
        carry = (num2->data + carry) / 10;
        num2 = num2->next;
    }
    if (carry > 0)
    {
        node *temp = newnode();
        temp->data = carry;
        temp->next = res;
        res = temp;
    }

    return res;

}
void print(node*head){
    if(!head){
        printf("list is empty");
        return;
    }
    while(head){
        printf(" %d",head->data);
        head=head->next;
    }
}
void reverselist(node**head){
    // printf("node head data=%d",(*head)->data);
	if(!*(head)||!((*head)->next)){
        // printf("reverse not possible");
		return;
	}
    node*p1=*head,*p2=(*head)->next,*p3=(*head)->next->next;
	while(p2!=NULL){
		if(p2->next==NULL){
			p2->next=p1;
			(*head)->next=NULL;
			(*head)=p2;
			break;
		}
		p2->next=p1;
		p1=p2;
		p2=p3;
		p3=p3->next;
	}
}
struct BigInteger mul(struct BigInteger n1,struct BigInteger n2){
    struct BigInteger res;
    res.head=NULL;
    if(n1.length<n2.length){
        struct BigInteger temp=n1;
        n1=n2;
        n2=temp;
    }
    node*num1=n1.head;
    node*num2=n2.head;
    node*head1=NULL;
    int carry=0,product=0;
    while(num1){
       product=((num1->data)*(num2->data)+carry);
       if(product>9){
        carry=product/10;
        product=product%10;
       }
       else{
       carry=0;
       }
       insertAtHead(&head1,product); 
       num1=num1->next;
    }
    if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
    num2=num2->next;
    res.head=head1;
    if(!num2){
        while(res.head->data==0&&res.head->next!=NULL){
        node*temp=res.head;
        temp=temp->next;
        res.head=temp;
    }
        return res;
    }
    reverse(&res);
    int itr=0;
    while(num2){
        itr++;
        head1=NULL;
        num1=n1.head;
        while(num1){
            product=(num1->data)*(num2->data)+carry;
            if(product>9){
                carry=product/10;
                product=product%10;
            }
            else
            carry=0;
            insertAtHead(&head1,product);
            num1=num1->next;
            // printf("\nhead1=");
            // print(head1);
            // printf("\n");
        }
        if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
        reverselist(&head1);
        num2=num2->next;
        res.head=addMul(head1,res.head,itr);
        reverse(&res);
    }
    reverse(&res);
    while(res.head->data==0&&res.head->next!=NULL){
        node*temp=res.head;
        temp=temp->next;
        res.head=temp;
    
    }
    return res;
}
//simple addition of two linked list

node *add2(node *num1,node *num2){
    node *ans=NULL;
    int carry=0,s=0;

    while(num1 && num2){

        s=(num1->data)+(num2->data)+carry;
        num1=num1->next;
        num2=num2->next;
        node *temp=newnode();

        carry=s/10;
        s=s%10;

        temp->data=s;

        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num1){
        s=num1->data+carry;
        num1=num1->next;
        carry=s/10;
        s=s%10;
        node *temp=newnode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num2){
        s=num2->data+carry;
        num2=num2->next;
        carry=s/10;
        s=s%10;
        node *temp=newnode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    if(carry){
        node *temp=newnode();
        temp->data=carry;
        temp->next=ans;
        ans=temp;
    }

    return ans;    
}
//subtract two linked list
node* Subtract_bigLinkedList(node *num1,node *num2){
    node *ans=NULL;

    while(num1 && num2){
        node *temp=newnode();
        if((num1->data)<(num2->data)){
            //case of borrowing carry
            //firstly we should be modifying our Linked list as we are borrowing
            borrow(num1->next);
            num1->data+=10;
        }
        temp->data=num1->data-num2->data;
        temp->next=ans;
        ans=temp;
        num1=num1->next;
        num2=num2->next;
    }

    while(num1){
        node *temp=num1->next;
        num1->next=ans;
        ans=num1;
        num1=temp;
    }

    while(ans->data==0) ans=ans->next;

    return ans;
}
int getLen(node *head){
    int len=0;
    while(head){
        len++;
        head=head->next;
    }
    return len;
}
int isSmaller(node *dividend,node *divisor){
    int len1=getLen(dividend),len2=getLen(divisor);
    if(len1<len2) return 0;
    else if(len1>len2) return 1;
    else{
        while(dividend){
            if(dividend->data > divisor->data)  return 1;
            else if(dividend->data < divisor->data) return 0;
            dividend=dividend->next;
            divisor=divisor->next;
        }
    }
    return 2;
}
struct BigInteger div1(struct BigInteger n1,struct BigInteger n2){
    struct BigInteger res;
    res.head=NULL;
    int k=compare(n1,n2);
    if(k==0){
        node*temp=newnode();
        temp->data=1;
        res.head=temp;
        return res;
    }
    else if(k==2){
        node*temp=newnode();
        temp->data=0;
        res.head=temp;
        return res;
    }
    struct BigInteger factor;
    factor.head=newnode();
    factor.head->data=1;
    node *one=newnode();
    one->data=1;
    reverse(&n1);
    int mark=1,sub=0;
    while(mark){
        struct BigInteger temp=mul(factor,n2);
        mark=isSmaller(n1.head,temp.head);
        if(mark==1){
            factor.head=add2(factor.head,one);
              reverse(&factor);
        }
        else if(mark==0){
            factor.head=Subtract_bigLinkedList(factor.head,one);
            sub=1;
            // if(option==5){
            //     reverselist(&temp);
            //     temp=Subtract_bigLinkedList(temp,n2.head);
            //     //num1=reverse(num1);
            //     node *rem=Subtract_bigLinkedList(n1.head,temp);
            //     reverselist(&rem);
            //     res.head=rem;
            //     return res;
            // }
            break;
        }
        else{
            // if(option==5){
            //     node *rem=newnode();
            //     rem->data=0;
            //     res.head=rem;
            //     return res;
            // }
            break;
        }
        // freeList(temp);
        // while(temp.head!=NULL){
        //     node*temp1=temp;
        //     temp=temp->next;
        //     free(temp1);
        // }
    }
    if(sub==0) reverse(&factor);
    res=factor;
    return res;
}