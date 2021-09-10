int *head = list.GetHead();
if (head != null) {
    int *fastPtr = head;
    int *slowPtr = head;

    bool isCircular = true;

    do
    {
        if (fastPtr->Next == null || fastPtr->Next->Next == null) //List end found
        {
            isCircular = false;
            break;
        }

        fastPtr = fastPtr->Next->Next;
        slowPtr = slowPtr->Next;
    } while (fastPtr != slowPtr);
    //确定环的起点
    slowPtr = head;
    while(slowPtr != fastPtr)
    {
        slowPtr = slowPtr->Next;
        fastPtr = fastPtr->Next;
    }
    cout<<"the starting point of the cycle is "<<slowPtr<<endl;
}
