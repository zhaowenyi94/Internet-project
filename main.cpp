#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>
#include <time.h>
#define LEN_PATRICIANODE sizeof(struct PatriciaTrieNode)
#define LEN_CHAR sizeof(char)
#define LEN_LINE 100
#define INI_LENGTH 10


char *ReadData(FILE *fp, char *buf)
{
    return fgets(buf, LEN_LINE, fp);
}
struct PatriciaTrieNode
{
    char* nodeKey;
    int nodeFlag;
    int nodeChildsNumber;
    int nodeSize;
    struct PatriciaTrieNode** nodeChildNodeList;
    struct PatriciaTrieNode* nodeParentNode;
    char nodeBitmapSet[255/(8*LEN_CHAR)+1];
    int nodePortNumber;
};
struct PatriciaTrieNode* initPatriciaNode(int flag,int port)
{
    int bitmapSize;
    struct PatriciaTrieNode* newNode=(struct PatriciaTrieNode *)malloc(sizeof(struct PatriciaTrieNode));
    newNode->nodeKey=(char*)"";
    newNode->nodeFlag=flag;
    newNode->nodeChildsNumber=0;
    newNode->nodeSize=0;
    newNode->nodeChildNodeList=(struct PatriciaTrieNode**)malloc(INI_LENGTH*sizeof(struct PatriciaTrieNode*));
    if(newNode->nodeChildNodeList !=NULL)
    {
        newNode->nodeSize = INI_LENGTH;
        for(int i = 0; i <newNode->nodeSize;i++ )
        {
            newNode->nodeChildNodeList[i] = NULL;
        }
    }
    newNode->nodeParentNode=NULL;
    if(newNode->nodeBitmapSet== NULL)
        return 0;
    bitmapSize = 255/(8*LEN_CHAR)+1;
    memset(newNode->nodeBitmapSet, 0x0, bitmapSize);
    newNode->nodePortNumber=port;
    return newNode;
}


void expandNodeSize(struct PatriciaTrieNode *node)
{
    int newallocsize = node->nodeChildsNumber+INI_LENGTH;
    struct PatriciaTrieNode **newList=(struct PatriciaTrieNode **)realloc(node->nodeChildNodeList,sizeof(struct PatriciaTrieNode *)*newallocsize);
    if(newList != NULL)
    {
        node->nodeChildNodeList=newList;
        node->nodeSize = newallocsize;
    }
    return ;
}
void insertNode(struct PatriciaTrieNode *node, int index, struct PatriciaTrieNode *tarNode)
{
    if(node->nodeChildsNumber + 1 > node->nodeSize)
    {
        expandNodeSize(node);
    }
    int i = 0;
    for(i = node->nodeChildsNumber; i >  index; )
    {
        node->nodeChildNodeList[i] = node->nodeChildNodeList[i - 1];
        i--;
    }
    node->nodeChildNodeList[index] = tarNode;
    node->nodeChildsNumber++;
}

void shrinkNodeSize(struct PatriciaTrieNode *node)
{
    if((node->nodeChildsNumber >> 1) <node->nodeSize && (node->nodeSize> INI_LENGTH))
    {
        int newallocsize = node->nodeChildsNumber+(node->nodeChildsNumber>>1) ;
        struct PatriciaTrieNode **newList = (struct PatriciaTrieNode **)realloc(node->nodeChildNodeList,sizeof(struct PatriciaTrieNode *)*newallocsize);
        if(newList != NULL)
        {
            node->nodeChildNodeList=newList;
            node->nodeSize = newallocsize;
        }
    }
    return;
}
void destroyNode(struct PatriciaTrieNode *node)
{
    if(node == NULL)
    {
        return;
    }
    node->nodeParentNode=NULL;
    free(node->nodeKey);
    node->nodeKey = NULL;
    free(node->nodeChildNodeList);
    node->nodeChildNodeList = NULL;
    free(node);
    node = NULL;
    return;
}

void deleteChildNode(struct PatriciaTrieNode *node, int index)
{
    int i = 0;
    destroyNode(node->nodeChildNodeList[index]);
    node->nodeChildNodeList[index]=NULL;
    for(i = index; (i+1) < node->nodeChildsNumber; i++)
    {
        node->nodeChildNodeList[i] = node->nodeChildNodeList[i + 1];
        node->nodeChildNodeList[i+1]=NULL;
    }
    
    node->nodeChildsNumber--;
    
    shrinkNodeSize(node);
    return;
}




struct PatriciaTrieNode* freePatriciaTrieNode(struct PatriciaTrieNode* node)
{
    free(node->nodeChildNodeList);
    node->nodeChildNodeList=NULL;
    node->nodeParentNode=NULL;
    //free(node->nodeParentNode);
    //node->nodeParentNode=NULL;
    free(node);
    node=NULL;
    return node;
}


char* cutStrMid(char* src,int startpos,int endpos)
{
    int Len=endpos-startpos;
    int OldLen = (int)strlen(src);
    if (endpos>OldLen) {
        Len=OldLen-startpos;
    }
    if(Len>=0){
        char * Result = (char*)malloc(Len + 1);
        memcpy(Result, src+startpos, Len);
        Result[Len] = '\0';
        return Result;
    }
    else
        return NULL;
    //    char *p;
    //    char *q;
    //    int n=endpos-startpos;
    //    int m=startpos;
    //    int len = (int)strlen(src);
    //    char* dst=(char*)malloc(n+1);
    //    if (dst==NULL)
    //    {
    //        printf("malloc error!");
    //        return NULL;
    //    }
    //    p = src;
    //    q = dst;
    //    if(n>len)
    //        n = len-m;
    //    if(m<0)
    //        m=0;
    //    if(m>len)
    //        return NULL;
    //    p += m;
    //    while(n--)
    //        *(q++) = *(p++);
    //    *(q++)='\0';
    //    return dst;
}

//cut a string after one pos
char* cutStrRight(char* src,int startpos)
{
    //    if (!cutStrMid(src, startpos, (int)strlen(src))) {
    //        printf("WWWWW!");
    //        return NULL;
    //    }
    return cutStrMid(src, startpos, (int)strlen(src));
}
char* longestprefix(char* str1,char* str2)
{
    char* p=str1;
    char* q=str2;
    char* buffer;
    int i=0;
    while (*p++==*q++) {
        i++;
    }
    buffer=cutStrMid(str1, 0, i);
    return buffer;
}


//the operations on the bitmap

int bitmap_setTo1(int index, char* bitmap)  //change the value on the position index from 0 to 1
{
    
    int subscript=index/(LEN_CHAR*8) ;
    int remainder = index%(LEN_CHAR*8);
    unsigned char x = (0x1<<remainder);
    if( subscript >255/(8*LEN_CHAR))
        return 0;
    bitmap[subscript] |= x;
    return 1;
}

int bitmap_setTo0(int index, char* bitmap)  //change the value on the position index from 1 to 0
{
    int subscript=index/(LEN_CHAR*8) ;
    int remainder = index%(LEN_CHAR*8);
    unsigned char x = (0x1<<remainder);
    if( subscript >255/(8*LEN_CHAR))
        return 0;
    bitmap[subscript] ^= x;
    return 1;
}


int bitmap_get(int index,char* bitmap)  //return 1 means the value in the position index is 1,return 0......is 0,return -1 means the index is out of the range
{
    //    int a=index;
    int subscript = index/(LEN_CHAR*8) ;
    int remainder = (index)%(LEN_CHAR*8);
    unsigned char x = (0x1<<remainder);
    unsigned char res;
    if( subscript > 255/(8*LEN_CHAR))
        return -1;
    res=bitmap[subscript] & x;
    return res > 0 ? 1 : 0;
}

void printBitmap(char*bitmap)
{
    int i;
    for(i=0;i<255;i++)
    {
        int a=bitmap_get(i, bitmap);
        printf("%d ",a);
    }
    printf("\n");
}

int bitmap_frontcount(int index,char* bitmap)
{
    int i,sum=0;
    for(i=0;i<index;i++)
    {
        sum+=bitmap_get(i, bitmap);
        //        if(bitmap_get(i, bitmap)==1)
        //            printf("%d\n", i);
    }
    //    printf("-------------------------------");
    return sum;
}

void addNode(struct PatriciaTrieNode* node,struct PatriciaTrieNode* tarNode)
{
    int index=0;
    if(bitmap_get(tarNode->nodeKey[0], node->nodeBitmapSet))//如果已经有了，替换
    {
        index=bitmap_frontcount(tarNode->nodeKey[0], node->nodeBitmapSet);
        node->nodeChildNodeList[index]=tarNode;
        tarNode->nodeParentNode=node;
    }
    else//否则添加
    {
        bitmap_setTo1(tarNode->nodeKey[0], node->nodeBitmapSet);
        index=bitmap_frontcount(tarNode->nodeKey[0], node->nodeBitmapSet);
        tarNode->nodeParentNode=node;
        //        node->nodeChildsNumber+=1;
        //        if((node->nodeChildsNumber)%INI_LENGTH==0)
        //            node->nodeChildNodeList=reallocate(node->nodeChildsNumber,node->nodeChildNodeList);
        //        for(int i=node->nodeChildsNumber-1;i>index;i--)
        //        {
        //            node->nodeChildNodeList[i]=node->nodeChildNodeList[i-1];
        //        }
        //        node->nodeChildNodeList[index]=tarNode;
        insertNode(node, index, tarNode);
    }
}

struct PatriciaTrieNode* searchStrInNode(char* targetStr,struct PatriciaTrieNode* node)
{
    while(/*(strcmp(node->nodeKey,"")!=0)||*/node->nodeChildNodeList[0])
    {
        if(strcmp(node->nodeKey,targetStr)!=0)
        {
            char* testCut=longestprefix(targetStr, node->nodeKey);
            if(strcmp(testCut,node->nodeKey)==0)
            {
                int index;
                char* remaining=cutStrRight(targetStr, (int)strlen(node->nodeKey));
                //
                targetStr+=(int)strlen(node->nodeKey);
                //
                index=remaining[0];
                if(bitmap_get(index, node->nodeBitmapSet)==1)
                {
                    int childnumber=bitmap_frontcount(index,node->nodeBitmapSet);
                    node=node->nodeChildNodeList[childnumber];
                    free(remaining);
                    remaining=NULL;
                }
                else
                {
                    free(remaining);
                    remaining=NULL;
                    return node;
                }
            }
            else
                return node;
        }
        else
            return node;
    }
    if(!node->nodeChildNodeList[0])
    {
        return node;
    }
    else
        return NULL;
    
}

int insertStrInNode(char* string,struct PatriciaTrieNode* node,int port)
{
    int sum=0;
    struct PatriciaTrieNode *testNode,*currnode;
    testNode=searchStrInNode(string, node);
    currnode=testNode;
    if(currnode->nodeParentNode==NULL)      //如果找到的最后需要验证的节点是root，有两种情况，第一种是root没有孩子，第二种是有孩子，如果有孩子我们需要重新排列孩子顺序，所以在此两种情况分开来说
    {
        
        struct PatriciaTrieNode* newnode=initPatriciaNode(3, port);
        newnode->nodeKey=string;
        addNode(currnode, newnode);
        
    }
    else  //如果找到的最终需要验证的节点不是root，remaining是待匹配的字符串，testnodekey是找到的最终节点的字符串
    {
        char *remaining,*testNodeKey;
        while(currnode->nodeParentNode)
        {
            sum+=strlen(currnode->nodeParentNode->nodeKey);
            currnode=currnode->nodeParentNode;
        }
        remaining=cutStrRight(string,sum);
        
        testNodeKey=testNode->nodeKey;
        if(strlen(remaining)>=strlen(testNodeKey))  //如果长度上remaining>=testnodekey
        {
            char *buffer;
            buffer=longestprefix(remaining, testNodeKey);
            if(strcmp(buffer, testNodeKey)==0)  //如果testnodekey和remaining前部分完全相同，则需要在现有的testnode下增加节点并将remaining剩余部分存入
            {
                char* newNodeKey=cutStrRight(remaining,(int)strlen(testNodeKey));
                if(/*strcmp(newNodeKey,"")*/strlen(newNodeKey)!=0)
                {
                    struct PatriciaTrieNode* newNode=initPatriciaNode(3,port);
                    newNode->nodeKey=newNodeKey;
                    addNode(testNode, newNode);
                }
            }
            else if(strlen(buffer)==0)  //如果remaining和testnodekey完全不同，则需要将testnode移向他的父亲节点，然后再给testnode增加节点来储存remaining
            {
                struct PatriciaTrieNode* newNode;
                testNode=testNode->nodeParentNode;
                newNode=initPatriciaNode(3,port);
                newNode->nodeKey=remaining;
                addNode(testNode, newNode);
            }
            else  //剩下的就是remaining和testnodekey只有一部分匹配，那么这部分需要将他们相同的提出来建立一个新的节点，这个新的节点加为testnode的父亲节点，将原来testnodekey剩下的后半部分存到testnode中，将remaining剩下的福分存在新建立的testnode的兄弟节点中
            {
                char* newFatherKey=buffer;
                char* oldtestNodeKey=cutStrRight(testNodeKey,(int)strlen(buffer));
                char* newBroKey=cutStrRight(remaining, (int)strlen(buffer));
                struct PatriciaTrieNode* newFather=initPatriciaNode(2,0);
                struct PatriciaTrieNode* newBrother=initPatriciaNode(3,port);
                testNode->nodeKey=oldtestNodeKey;
                newFather->nodeKey=newFatherKey;
                newBrother->nodeKey=newBroKey;
                addNode(testNode->nodeParentNode, newFather);
                addNode(newFather, testNode);
                addNode(newFather, newBrother);
            }
        }
        else  //如果长度remaining<testnodekey，操作和大于等于基本相同，不过remaining和testnodekey调换位置
        {
            char *buffer;
            buffer=longestprefix(remaining, testNodeKey);
            if(strcmp(buffer,remaining)==0)
            {
                char *oldNodeKey=cutStrRight(testNodeKey, (int)strlen(remaining));
                struct PatriciaTrieNode* newNode=initPatriciaNode(3,port);
                newNode->nodeKey=buffer;
                testNode->nodeKey=oldNodeKey;
                addNode(testNode->nodeParentNode, newNode);
                addNode(newNode, testNode);
            }
            else if(strlen(buffer)==0)
            {
                struct PatriciaTrieNode* newNode;
                testNode=testNode->nodeParentNode;
                newNode=initPatriciaNode(3,port);
                newNode->nodeKey=remaining;
                addNode(testNode, newNode);
            }
            else
            {
                char* newFatherKey=buffer;
                char* oldtestNodeKey=cutStrRight(testNodeKey,(int)strlen(buffer));
                char* newBroKey=cutStrRight(remaining, (int)strlen(buffer));
                struct PatriciaTrieNode* newFather=initPatriciaNode(2,0);
                struct PatriciaTrieNode* newBrother=initPatriciaNode(3,port);
                testNode->nodeKey=oldtestNodeKey;
                newFather->nodeKey=newFatherKey;
                newBrother->nodeKey=newBroKey;
                addNode(testNode->nodeParentNode, newFather);
                addNode(newFather, testNode);
                addNode(newFather, newBrother);
            }
        }
    }
    return 1;
    
}

void getPort(struct PatriciaTrieNode* node)
{
    printf("%d\n",node->nodePortNumber);
}


int delete(char* string,struct PatriciaTrieNode* node)
{
    int flag=1;
    int sum,index;
    char *remaining,*testNodeKey;
    struct PatriciaTrieNode *testNode,*currnode;
    sum=0;
    testNode=searchStrInNode(string, node);
    currnode=testNode;
    while(currnode->nodeParentNode)
    {
        sum+=strlen(currnode->nodeParentNode->nodeKey);
        currnode=currnode->nodeParentNode;
    }
    remaining=cutStrRight(string,sum);
    testNodeKey=testNode->nodeKey;
    if(strlen(remaining)<strlen(testNodeKey))
    {
        printf("No compatible things!\n");
        free(remaining);
        remaining=NULL;
        return 0;
    }
    else
    {
        char* test=longestprefix(remaining, testNodeKey);
        free(remaining);
        remaining=NULL;
        if(strcmp(test,testNodeKey)!=0)
        {
            printf("No compatible things!\n");
            free(test);
            test=NULL;
            return 0;
        }
        free(test);
        test=NULL;
    }
    if(!testNode->nodeParentNode)
    {
        printf("No compatible things!\n");
        return 0;
    }
    while(testNode->nodeParentNode)
    {
        if(testNode->nodeFlag==3)
        {
            flag=0;
            if(testNode->nodeChildsNumber==0)
            {
                getPort(testNode);
                index=bitmap_frontcount(testNode->nodeKey[0], testNode->nodeParentNode->nodeBitmapSet);
                bitmap_setTo0(testNode->nodeKey[0], testNode->nodeParentNode->nodeBitmapSet);
                testNode=testNode->nodeParentNode;
                deleteChildNode(testNode, index);
                //destroyNode(killnode);
            }
            else
            {
                testNode->nodeFlag=2;
                getPort(testNode);
                testNode=testNode->nodeParentNode;
            }
        }
        else if(testNode->nodeFlag==2&&testNode->nodeChildsNumber==0)
        {
            index=bitmap_frontcount(testNode->nodeKey[0], testNode->nodeParentNode->nodeBitmapSet);
            bitmap_setTo0(testNode->nodeKey[0], testNode->nodeParentNode->nodeBitmapSet);
            testNode=testNode->nodeParentNode;
            deleteChildNode(testNode, index);
        }
        else
        {
            if(flag==1)
            {
                printf("No compatible things!\n");
                flag=0;
            }
            testNode=testNode->nodeParentNode;
        }
        
    }
    return 1;
    
    
}





int main()
{
    clock_t a,b;
    double sum=0;
    
    struct PatriciaTrieNode* root=initPatriciaNode(0,0);
    FILE *fp1,*fp2;
    int i=0;
    if((fp1=fopen("/Users/zhaowenichi/Downloads/toStudent/url-list-alexa.txt","r"))==NULL)
    {
        printf("File open error\n");
        return 0;
    }
    if((fp2=fopen("/Users/zhaowenichi/Downloads/toStudent/url-list-alexa.txt","r"))==NULL)
    {
        printf("File open error\n");
        return 0;
    }
    while (1) {
        char *p,*p1,*buf,*buf1;
        buf=(char*)malloc(LEN_LINE*sizeof(char));
        buf1=(char*)malloc(LEN_LINE*sizeof(char));
        if (i<1000000) {
            p=ReadData(fp1, buf);
            if(!p)
                break;
            buf=cutStrMid(buf, 0, (int)strlen(buf)-2);
            a=clock();
            insertStrInNode(buf, root, i++);
            b=clock();
        }
        if (i>500000) {
            p1=ReadData(fp2, buf1);
            if(!p1)
                break;
            buf1=cutStrMid(buf1, 0, (int)strlen(buf1)-2);
            a=clock();
            delete(buf1, root);
            b=clock();
        }
        free(buf1);
        buf1=NULL;
        sum+=(double)(b-a)/CLOCKS_PER_SEC;
    }
    fclose(fp1);
    fclose(fp2);
    printf("%f",sum);
    return 0;
}