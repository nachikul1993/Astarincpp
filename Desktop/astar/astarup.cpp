#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

struct node{
	char data[7];
	int h;
	int f;
	node *parent;
	node *child[6];
}*reqd;

class astar{

	int gencost;
	int ch;
	public:
		node *startnode,*goal;
		node *open[100];
		node *closed[100];
			
		int opencnt;
		int closdcnt;
		int childcnt;
		
		astar()
		{
			gencost=0;
			ch=0;
			startnode=new node();
			//startnode=NULL;
			goal=new node();
			//goal=NULL;
			opencnt=0;
			closdcnt=0;
			childcnt=0;
			for(int i=0;i<100;i++)
			{
				open[i]=new node;
				//open[i]=NULL;
				closed[i]=new node;
				//closed[i]=NULL;
			}		
		}
		void initnode(node *a)
		{
			for(int i=0;i<6;i++)
			{
				a->child[i]=new node;
				//a->child[i]=NULL;
			}
		}		
		void swap(node *a,int k,int l)
		{
			char c;
			c=a->data[k];
			a->data[k]=a->data[l];
			a->data[l]=c;
		}	
		void calcheu(node *n,int k)
		{
			int tmp=0;
			for(int i=0;i<7;i++)
				{
				  if(n->data[i]!=goal->data[i])
				  	tmp++;  	
				}
				n->h=tmp;
				if(tmp==0) {n->f=0; n->h=0;}  				
				else {	
					n->f=(n->h)+k;
				}
				
		}
			
		void getdata()
		{

			cout<<"\n Enter startnode data (B W E - blank):"<<endl;
			for(int i=0;i<7;i++)
				{
					cin>>startnode->data[i];				
				}
			
			open[0]=startnode;		
			cout<<"\n Enter goalnode data (B W E - blank):"<<endl;
			for(int i=0;i<7;i++)
				{
					cin>>goal->data[i];	
				}	
			
			
			cout<<"\n By f(x) or by h(x) ? 1/2 : ";	
			cin>>ch;	
			goal->f=0;	
			calcheu(startnode,0);	
			createtree(startnode);					
		}
		void sortnode()
		{
			node *temp=new node;
			int tmp1=0;
			int tmp2=0;
				for(int i=0;i<opencnt;i++)
				{
					for(int j=i+1;j<opencnt;j++)
					{
						if(ch==1) {tmp1=open[j]->f; tmp2=open[i]->f;}
						else{tmp1=open[j]->h; tmp2=open[i]->h;}	 
						if(tmp1<tmp2)
							{
							temp=open[i];
							open[i]=open[j];
							open[j]=temp;
							}
					}
				}			
		}			
		
	        int checkopen(node *a)
		{
			int flag=0;
			for(int i=0;i<opencnt || i<closdcnt;i++)
			{
				if(strcmp(open[i]->data,a->data)==0)
				{
					if(open[i]->f<a->f)
						{a=NULL; flag=1;}
					else if(open[i]->f > a->f)
						{
						a->parent=open[i]->parent;
						open[i]=NULL;
						open[i]=a;
						flag=1;
						}
					else flag=0;
				return 0;	
				}
				if(strcmp(closed[i]->data,a->data)==0)
				{
					flag==1;
				return 0;	
				}						
			}
			if(flag==0) { 
					return 1;}
		}			
		void genchild(node *t,int i,int j,int heu)
		{
			int tmp1=0;
			strcpy(t->child[childcnt]->data,t->data);
			swap(t->child[childcnt],i,j);
			calcheu(t->child[childcnt],heu);	
			
			int p=checkopen(t->child[childcnt]);			
			if(p==1) {
			gencost=gencost+1;
			++opencnt;
			if(ch==1){tmp1=t->child[childcnt]->f;}
			else{tmp1=t->child[childcnt]->h;}	
			cout<<"\t"<<t->child[childcnt]->data<<"|"<<tmp1;
			t->child[childcnt]->parent=t;
					//cout<<"\n"<<opencnt; 
					open[opencnt]=t->child[childcnt];	 
			if(t->child[childcnt]->f==0) createtree(t->child[childcnt]);			
			childcnt++; }
				
		}
	
		void createtree(node *);
		void childs(node *);
};		
	
void astar::createtree(node *p)
{
	int low;
	low=50;
	int num=0;
	node *current_node=new node;
	if(strcmp(p->data,goal->data)!=0)
	{
		
		for(int k=0;k<=opencnt;k++)
		{
		if(open[k]==p)
		{
			
			for(int l=k;l+1<=opencnt;l++)
			{
				open[l]=open[l+1];			
			}
		}
		}
		
		//open[opencnt]=NULL;
		opencnt=opencnt-1;
		closed[closdcnt++]=p;						
		cout<<"\n"<<p->data<<"\n \n";		
		childs(p);
		sortnode();

		current_node=open[num];	 
		createtree(current_node);		
	}
	else{
		cout<<"\n GOAL REACHED";
		cout<<"\n"<<p->data<<endl;
		current_node=p;
		int pcost;
		while(current_node!=NULL)
			{
				pcost+=1;
				cout<<"\t -->"<<current_node->data;
				current_node=current_node->parent;
			}
		cout<<"\n PATH COST is : "<<pcost;
		cout<<"\n TOTAL COST is :"<<gencost<<"\n";	
		exit(0);	
	}
}	

void astar::childs(node *t)
{
	int i;
	int cnt=0;
	int u=1;	
	childcnt=0;
	int tmp;
		
	initnode(t);
	for(i=0;i<7;i++)
		{
			if(t->data[i]=='E') break;
		}
	switch(i){
	case 0:		
		genchild(t,0,1,1);
		genchild(t,0,2,1);
		genchild(t,0,3,2);
		break;
	case 1:
		genchild(t,1,0,1);
		genchild(t,1,2,1);
		genchild(t,1,3,1);
		genchild(t,1,4,2);
		break;	
	case 2:
		genchild(t,2,0,1);
		genchild(t,2,1,1);
		genchild(t,2,3,1);
		genchild(t,2,4,1);
		genchild(t,2,5,2);
		break;
	case 3:
		genchild(t,3,0,2);
		genchild(t,3,1,1);
		genchild(t,3,2,1);
		genchild(t,3,4,1);
		genchild(t,3,5,1);
		genchild(t,3,6,2);
		break;
	case 4:
		genchild(t,4,1,2);
		genchild(t,4,2,1);
		genchild(t,4,3,1);
		genchild(t,4,5,1);
		genchild(t,4,6,1);
		break;
	case 5:
		genchild(t,5,2,2);
		genchild(t,5,3,1);
		genchild(t,5,4,1);
		genchild(t,5,6,1);
		break;
	case 6:
		genchild(t,6,3,2);
		genchild(t,6,4,1);
		genchild(t,6,5,1);
		break;
									
}

}
int main()
{
	astar o;	
	o.getdata();
	return 0;
}
