/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"
#include "cmath"
#include "string.h"
#define BST (+0)
#define ZERO                    0e-5
#define STOP                    5e-3
struct Data {
    L1List<L1List<VRecord>> NewDataList;
    L1List<VRecord> CopyDataList;
    int flag;
    int flag_copy;
};
/// Initialize and Finalize any global data that you use in the program
// bool Test2chieu(L1List<L1List<VRecord>> &NewDataList, int& flag){
//     int flag=1;
//     L1Item<L1List<VRecord>>* pFirst = NewDataList.getpHead();
//     if (flag == 1){
//     while (pFirst!= NULL){
//         L1Item<VRecord>* tester = pFirst->data.getpHead();
//         L1Item<VRecord>* child =  tester;
//         while(child->pNext !=NULL){
//             if (strcmp(tester->data.id,child->pNext->data.id)!=0){
//                 cout<< child->data.id;
//                 flag=0;
//                 break;
//             }
//             else{
//                 child=child->pNext;
//             }
//         }
//         pFirst=pFirst->pNext;
//     }
//     if(flag) return true;
//     else return false;
//      flag++;
//      }
// }
bool CreateListID(L1List<VRecord>& recList, L1List<L1List<VRecord>> &NewDataList, int &flag) {
    if(flag == 0) {
        while(recList.getSize()) {
            L1List<VRecord>* db = new L1List<VRecord>(); // lieu sau moi vong while db co thay doi
            L1Item<VRecord>* p = recList.getFirst();
            //db.insertHead(p->data);
            db->insertHead(p);
            L1Item<VRecord>* pCurr = recList.getpHead();
            L1Item<VRecord>* pPre = NULL;
            int t=0;
            while (pCurr != NULL){
                if (strcmp(pCurr->data.id,p->data.id)==0) {
                    if (t==0){
                        pCurr=pCurr->pNext;
                        L1Item<VRecord>* CNode=recList.getFirst();
                        db->insertHead(CNode);
                    }
                    else{
                        L1Item<VRecord>* CNode=pCurr;
                        pPre->pNext=pCurr->pNext;
                        pCurr=pCurr->pNext;
                        db->insertHead(CNode);
                        recList.decreaseSize();
                        t++;
                    }
                }else{
                    pPre=pCurr;
                    pCurr=pCurr->pNext;
                    t++;
                }
                
                
            }
            // duyet reclist tim node co id giong id node dau cua db bo vao db
            db->reverse();
            L1Item<L1List<VRecord>>* New = new L1Item<L1List<VRecord>>((*db));
            NewDataList.insertHead(New); // db co thay doi ?
        }
        NewDataList.reverse();
        //cout << recList.getSize() << endl;
        flag++;
        return true;
    }
    return false;
}

/*
int Number_Data(L1List<L1List<VRecord>>& NewDataList) {
    return NewDataList.getSize();
}
*/

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    static Data* pGList = new Data;
    pGList->flag_copy=0; 
    pGList->flag = 0;
    *pGData = pGList;
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}
bool CopyRec(L1List<VRecord>& recList,L1List<VRecord>& copyitem,int& flag){
    if (flag == 0){
    L1Item<VRecord>* pNew = recList.getpHead();
        while(pNew!=NULL){
            L1Item<VRecord>* pTemp =new L1Item<VRecord>();
            strcpy(pTemp->data.id,pNew->data.id);
            pTemp->data.timestamp=pNew->data.timestamp;
            pTemp->data.x=pNew->data.x;
            pTemp->data.y=pNew->data.y;
            copyitem.insertHead(pTemp);
            pNew=pNew->pNext;
        }
    copyitem.reverse();
    flag++;
    return true;
    } 
    return false;
}
bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    Data* pGList = (Data*) pGData;
    CopyRec(recList,pGList->CopyDataList, pGList->flag_copy);
    if(CreateListID(recList, pGList->NewDataList, pGList->flag)) {
    }
    else {
    }
    //Test2chieu(pGList->NewDataList, pGList->flag);
    switch(request.code[0]) {
        case 'C': {
            switch(request.code[1]) {
                case 'N': {
                    switch(request.code[2]) {
                        case 'V': {
                            cout<<"CNV: ";
                            cout << pGList->NewDataList.getSize() << endl;
                            break;
                        }
                        case 'R': {
                            cout<< "CNR: ";
                            cout <<  pGList->CopyDataList.getSize() << endl;
                            break;
                        }
                        default: {
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            // int t = 0;
                            // char** idmove=new char*[pGList->NewDataList.getSize()];
                            int idmove=0;
                            int flagmov=0;
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                while (child->pNext != NULL)
                                {
                                    
                                    if (distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x) <= STOP){
                                       flagmov=1;
                                    } 
                                    child=child->pNext;
                                }
                                if (flagmov==0) {
                                    idmove++;
                                }
                                pFirst=pFirst->pNext;
                                flagmov = 0;
                            }
                            if (idmove==0){
                                cout<<request.code;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            else{
                                cout<<request.code;
                                cout<<": ";
                                cout << idmove;
                                cout<<endl;
                            }
                        }
                    }
                    break;
                }
                default: {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    double sumdis=0 ;
                    double record= 0;
                    double device= 0;
                    while (pFirst!= NULL){
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        record=pFirst->data.getSize();
                        while (child->pNext != NULL)
                        {
                            sumdis =   sumdis + distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x)*1000;
                            child=child->pNext;
                        }
                        device = device + record - 1;
                        pFirst=pFirst->pNext;
                    } 
                    cout<<"CAS: ";
                    cout<<setprecision(6) << sumdis/device <<" meter"<<endl ;
                    break;
                }    //// CAS
            }
            break;
        }
        case 'V': {
            switch(request.code[1]) {
                case 'F': {
                    switch(request.code[2]) {
                        case 'F': {
                            /*
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            L1Item<VRecord>* pFF = pFirst->data.getpHead();
                            cout << "Thiet bi duoc luu tru dau tien la: ";
                            cout << pFF->data.id << endl;
                            */
                            cout<<"VFF: ";
                            cout << pGList->NewDataList.getpHead()->data.getpHead()->data.id << endl;
                            //printVRecord(pGList->NewDataList.getpHead()->data.getpHead()->data);
                            break;
                        }
                        case 'L': {
                            cout<<"VFL: ";
                            //L1Item<VRecord>* 
                            L1Item<L1List<VRecord>>*Lastitem = pGList->NewDataList.getpHead();
                            while(Lastitem->pNext!=NULL) {
                                Lastitem = Lastitem->pNext;
                            }
                            cout <<Lastitem->data.getpHead()->data.id <<endl;
                            break;
                        }
                        case 'Y': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            const char* s = "Y";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                tempID=(string)pFirst->data.getpHead()->data.id;
                                if (tempID==rID){
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< setprecision(6) << pFirst->data.getpHead()->data.y;
                                    cout<<endl;
                                    break;
                                }
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;   
                        }
                        case 'X': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            const char* s = "X";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                tempID=(string)pFirst->data.getpHead()->data.id;
                                if (tempID==rID){
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< setprecision(6) << pFirst->data.getpHead()->data.x;
                                    cout<<endl;
                                    break;
                                }
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;   
                        }
                        case 'T': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            struct tm *info;
                            char buffer[80];
                            const char* s = "T";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;

                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                tempID=(string)pFirst->data.getpHead()->data.id;
                                if (tempID==rID){
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    info =gmtime( &pFirst->data.getpHead()->data.timestamp );
                                    info->tm_hour=(info->tm_hour+BST)%24;
                                    strftime(buffer,80,"%y-%m-%d %X", info);
                                    cout<< buffer;
                                    cout<<endl;
                                    break;
                                }
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                        default: {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double tempx=0;
                            double tempy=0;
                            const char* s = "S";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) == 0){
                                            tempx=child->pNext->data.x;
                                            tempy=child->pNext->data.y;
                                            flag=1;
                                            cout<<y;
                                            cout<<": ";
                                            cout<<"(";
                                            cout<<tempx;
                                            cout<<",";
                                            cout<<tempy;
                                            cout<<")";
                                            cout<<endl;
                                            break;
                                        } 
                                        child=child->pNext;
                                    }
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": non stop!";
                                cout<<endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 'L': {
                    switch(request.code[2]) {
                        case 'Y': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double lasttime;
                            const char* s = "Y";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        child=child->pNext;
                                    }
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< setprecision(6) << child->data.y;
                                    cout<<endl;
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                        case 'X': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double lasttime;
                            const char* s = "X";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        child=child->pNext;
                                    }
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< setprecision(6) << child->data.x;
                                    cout<<endl;
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                        case 'T': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double lasttime;
                            struct tm *info;
                            char buffer[80];
                            const char* s = "T";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        child=child->pNext;
                                    }
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    info =gmtime( &child->data.timestamp );
                                    info->tm_hour=(info->tm_hour+BST)%24;
                                    strftime(buffer,80,"%y-%m-%d %X", info);
                                    cout<< buffer;
                                    cout<<endl;
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break; 
                        }
                        default: {
                            /////////////////////////////////////////////////////////////////////////////
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double tempx=0;
                            double tempy=0;
                            const char* s = "S";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) == 0){
                                            tempx=child->pNext->data.x;
                                            tempy=child->pNext->data.y;
                                            flag=1;
                                        } 
                                        child=child->pNext;
                                    }
                                } 
                                if(flag) {
                                    cout<<y;
                                    cout<<": ";
                                    cout<<"(";
                                    cout<< tempx;
                                    cout<<",";
                                    cout<<tempy;
                                    cout<<")";
                                    cout<<endl;
                                    break;
                                }
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": non stop!";
                                cout<<endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 'C': {
                    switch(request.code[2]) {
                        case 'R': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            const char* s = "R";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                tempID=(string)pFirst->data.getpHead()->data.id;
                                if (tempID==rID){
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< pFirst->data.getSize();
                                    cout<<endl;
                                    break;
                                }
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                        default: {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            double longdis=0;
                            const char* s = "L";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        //if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) > 0){
                                            longdis =   longdis + distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x);
                                        //} 
                                        child=child->pNext;
                                    }
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< setprecision(6) << longdis;
                                    cout<<endl;
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 'M': {
                    switch(request.code[2]) {
                        case 'T': {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            size_t tempmax=0;
                            const char* s = "T";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) > 0){
                                            tempmax =   tempmax + difftime(child->pNext->data.timestamp,child->data.timestamp);
                                        } 
                                        child=child->pNext;
                                    }
                                    flag=1;
                                    cout<<y;
                                    cout<<": ";
                                    cout<< tempmax;
                                    cout<<endl;
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": Failed";
                                cout<<endl;
                            }
                            break;
                        }
                        default: {
                            string y= (string)request.code;
                            int flag=0;
                            string tempID;
                            string rID;
                            size_t tempmax=0;
                            const char* s = "S";
                            char* tID=strtok(request.code,s);
                            tID=strtok(NULL,s);
                            rID=(string)tID;
                            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                            while (pFirst!= NULL){
                                L1Item<VRecord>* child = pFirst->data.getpHead();
                                tempID=(string)child->data.id;
                                if (tempID==rID){
                                    while (child->pNext != NULL){
                                        if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) == 0){
                                            if (tempmax < difftime(child->pNext->data.timestamp,child->data.timestamp))
                                            tempmax=difftime(child->pNext->data.timestamp,child->data.timestamp);
                                        } 
                                        child=child->pNext;
                                    }
                                    if (tempmax>0){
                                        flag=1;
                                        cout<<y;
                                        cout<<": ";
                                        cout<< tempmax;
                                        cout<<endl;
                                    } 
                                } 
                                if(flag) break;
                                pFirst=pFirst->pNext;
                            }
                            if (!flag){
                                cout<<y;
                                cout<<": non stop!";
                                cout<<endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {
                    string y= (string)request.code;
                    int flag=0;
                    string tempID;
                    string rID;
                    double tempmax=0;
                    int t=0;
                    const char* s = "S";
                    char* tID=strtok(request.code,s);
                    tID=strtok(NULL,s);
                    rID=(string)tID;
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    while (pFirst!= NULL){
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        tempID=(string)child->data.id;
                        if (tempID==rID){
                            while (child->pNext != NULL){
                                t++;
                                tempmax= tempmax + distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x);       
                                child=child->pNext;
                            }
                            flag=1;
                            cout<<y;
                            cout<<": ";
                            //cout<<tID <<" ";
                            cout<<setprecision(6)<< tempmax/t*1000<< " meter";
                            cout<<endl;
                        } 
                        if(flag) break;
                        pFirst=pFirst->pNext;
                    }
                    if (!flag){
                        cout<<y;
                        cout<<": Failed";
                        cout<<endl;
                    }
                    break;
                }
            }
            break;
        }
        case 'M': {
            switch(request.code[1]) {
                case 'S': {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    double tempstop=0 ;
                    double maxstop=0 ; 
                    char* idstop ;
                    // char* tempid;
                    // int k= 1;
                    int flag=0;
                    while (pFirst!= NULL){
                        // k=1;
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        while (child->pNext != NULL)
                        {
                            // k++;
                            if (distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x) == 0){
                                tempstop =   tempstop + difftime(child->pNext->data.timestamp,child->data.timestamp);
                            } 
                            child=child->pNext;
                        }
                        if ( tempstop > maxstop ){
                            maxstop = tempstop;
                            idstop=pFirst->data.getpHead()->data.id;
                            flag=1;
                        }
                        
                        // if (tempstop>0){
                        //     tempid=pFirst->data.getpHead()->data.id;
                        //     cout<< tempstop << " la "<< tempmax <<" s "<< k <<" record"<<endl ;
                        // }
                        // else q++;
                        tempstop=0;
                        pFirst=pFirst->pNext;
                    }
                    if(flag){
                        cout<<request.code;
                        cout<<": ";
                        //cout << idstop <<" ";
                        cout<< setprecision(0) << maxstop <<"s"<<endl ;
                    }else{
                        cout<<request.code;
                        cout<<": Failed";                        
                    }
                    break;
                }
                case 'R': {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    //char** maxid = new char*[pGList->NewDataList.getSize()]; 
                    char* maxid;
                    size_t max = pFirst->data.getSize();
                    while (pFirst->pNext!= NULL){
                        pFirst=pFirst->pNext;
                        if (max < pFirst->data.getSize()) {
                            max = pFirst->data.getSize();
                            maxid = pFirst->data.getpHead()->data.id;
                        }
                    }
                    // pFirst = pGList->NewDataList.getpHead();
                    // int t=0;
                    // while (pFirst->pNext!= NULL){
                    //     pFirst=pFirst->pNext;
                    //     if (max == pFirst->data.getSize()) {
                    //         //maxid [t] = pFirst->data.getpHead()->data.id;
                    //         t++;
                    //     }
                    // }
                   /* cout<<maxid<<endl;
                    cout<<max<<endl;
                    pFirst=pFirst->pNext;
                    maxid = pFirst->data.getpHead()->data.id;
                    max = pFirst->data.getSize();*/
                    //cout<< "thiet bi co record nhieu nhat: " <<maxid<< " la "<<max<<" record"<<endl;
                    //for (int i=0; i < t;i++){
                        cout<<"MRV: ";
                        cout<< maxid<<endl;
                        //cout<<" "<<"la "<<max<<" record"<<endl;
                    //}
                    break;
                }
                case 'T': {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    double tempmax=0 ;
                    double maxtime=0 ;
                    int flag=0; 
                    char* idtime ;
                    // char* tempid;
                    // int k= 1;
                    while (pFirst!= NULL){
                        // k=1;
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        while (child->pNext != NULL)
                        {
                            // k++;
                            if (distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x) > 0){
                                tempmax =   tempmax + difftime(child->pNext->data.timestamp,child->data.timestamp);
                            } 
                            child=child->pNext;
                        }
                        if ( tempmax > maxtime ){
                            maxtime=tempmax;
                            idtime=pFirst->data.getpHead()->data.id;
                            flag=1;
                        }
                        
                        // if (tempmax>0){
                        //     tempid=pFirst->data.getpHead()->data.id;
                        //     cout<< tempid << " la "<< tempmax <<" s "<< k <<" record"<<endl ;
                        // }
                        // else q++;
                        tempmax=0;
                        pFirst=pFirst->pNext;
                    }
                    if(flag){
                        cout<<request.code;
                        cout<<": ";
                        cout<<idtime <<endl;
                        //cout<< " la "<< maxtime <<" s"<<endl ;
                    }else{
                        cout<<request.code;
                        cout<<": Failed";
                    }
                    break;
                }
                default: {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    double temptime=0 ;
                    double tempdis=0 ;
                    double tempsp =0;
                    double maxsp =0 ;
                    int flag=0;
                    char* idtime ;
                    // char* tempid;
                    // int k= 1;
                    while (pFirst!= NULL){
                        // k=1;
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        while (child->pNext != NULL)
                        {
                            // k++;
                            if (distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y) > 0){
                                temptime =   temptime + difftime(child->pNext->data.timestamp,child->data.timestamp);
                                tempdis =   tempdis + distanceVR(child->data.x,child->data.y,child->pNext->data.x,child->pNext->data.y);
                            } 
                            child=child->pNext;
                        }
                        tempsp = tempdis/temptime;
                        if ( tempsp > maxsp ){
                            maxsp=tempsp;
                            idtime=pFirst->data.getpHead()->data.id;
                            flag=1;
                        }
                        temptime=0;
                        tempdis =0;
                        tempsp  =0;
                        pFirst=pFirst->pNext;
                    }
                    if (flag){
                        cout<<request.code;
                        cout<<": ";
                        cout<< idtime <<endl;
                        //cout<< " la "<< maxsp <<" m/s"<<endl ;
                    }else{
                        cout<<request.code;
                        cout<<": Failed";
                    }
                    break;
                }
            }
            break;
        }
        case 'L': {
            switch(request.code[1]) {
                case 'R': {
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    //char** minid = new char*[pGList->NewDataList.getSize()];  
                    char * minid;
                    int flag=0;
                    size_t min = pFirst->data.getSize();
                    while (pFirst->pNext!= NULL){
                        pFirst=pFirst->pNext;
                        if (min > pFirst->data.getSize()) {
                            min = pFirst->data.getSize();
                        }
                    }
                    pFirst = pGList->NewDataList.getpHead();
                    int t=0;
                    while (pFirst->pNext!= NULL){
                        pFirst=pFirst->pNext;
                        if (min == pFirst->data.getSize()) {
                            //minid[t] = pFirst->data.getpHead()->data.id;
                            //t++;
                            flag=1;
                            minid= pFirst->data.getpHead()->data.id;
                            cout<<request.code;
                            cout<<": ";
                            cout<<minid;
                            cout<<endl;
                            break;
                        }
                    }
                    if (!flag){
                        cout<<request.code;
                        cout<<": Failed";
                    } 
                    // cout<< "thiet bi co record it nhat: ";
                    // for (int i=0; i < t;i++){
                    //     cout<<minid[i]<<" ";
                    // }
                    // cout<<"la "<<min<<" record"<<endl;
                    break;
                }
                default: {
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
                    L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
                    double maxdis=0 ;
                    double tempdis=0 ;
                    char* iddis ;
                    int flag=0;
                    // char* tempid;
                    // int k= 1;
                    while (pFirst!= NULL){
                        // k=1;
                        L1Item<VRecord>* child = pFirst->data.getpHead();
                        while (child->pNext != NULL)
                        {
                            // k++;
                            if (distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x) > 0){
                                tempdis =   tempdis + distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x);
                            } 
                            child=child->pNext;
                        }
                        if ( tempdis > maxdis ){
                            maxdis=tempdis;
                            iddis=pFirst->data.getpHead()->data.id;
                            flag=1;
                        }
                        tempdis =0;
                        pFirst=pFirst->pNext;
                    }
                    if(flag){
                        cout<<request.code;
                        cout<<": ";
                        //cout<< " Thiet bi co hanh trinh dai nhat " ;
                        cout<< iddis<<endl; 
                        //cout<< " la "<< maxdis <<" m"<<endl ;  
                    }else{
                        cout<<request.code;
                        cout<<": Failed";                        
                    }              
                    break;
                }
            }
            break;
        }
        case 'S': {
            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
            double mindis=0 ;
            double tempdis=0 ;
            int a = 0;
            int flag=0; 
            char* iddis;
            while (pFirst!= NULL){
                L1Item<VRecord>* child = pFirst->data.getpHead();
                while (child->pNext != NULL)
                {
                    tempdis =   tempdis + distanceVR(child->data.y,child->data.x,child->pNext->data.y,child->pNext->data.x); 
                    child=child->pNext;
                    
                }
                if (pFirst->data.getpHead()->data.id=="51B03755"){
                    cout<<setprecision(3)<< tempdis*1000<<" ";
                }
                
                if (!a) {
                    if(tempdis > 0){
                        mindis=tempdis;
                        iddis=pFirst->data.getpHead()->data.id;
                        cout<<"lay ";
                        flag = 1;
                        a = 1;
                    } 
                }
                if ( tempdis < mindis ){
                    if(tempdis > 0){
                        mindis=tempdis;
                        iddis=pFirst->data.getpHead()->data.id;
                        cout<<"lay ";
                        flag=1;
                    }
                }
                tempdis =0;
                pFirst=pFirst->pNext;
            }
            if (flag){
                cout<<request.code;
                cout<<": Succeed";
                cout<< " Thiet bi co hanh trinh ngan nhat " << iddis << " la "<< mindis <<" m"<<endl ;  
            }
            else{
                cout<<request.code;
                cout<<": Failed";
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////
        default: {
            string y= (string)request.code;
            int flag=0;
            string tempID;
            string rID;
            int t=0;
            const char* s = "R";
            char* tID=strtok(request.code,s);
            tID=strtok(NULL,s);
            rID=(string)tID;
            L1Item<L1List<VRecord>>* pFirst = pGList->NewDataList.getpHead();
            L1Item<L1List<VRecord>>* pPre =NULL;
            while (pFirst!= NULL){
                t++;
                tempID=(string)pFirst->data.getpHead()->data.id;
                if (tempID==rID){
                    flag=1;
                    cout<<y;
                    cout<<": Succeed";
                    cout<<endl;
                    if (t==1){
                        pGList->NewDataList.removeHead();
                    }
                    else{
                        pPre->pNext=pFirst->pNext;
                        delete pFirst;
                    }
                    break;
                }
                pPre = pFirst;
                pFirst=pFirst->pNext;
            }
            t=0;
            L1Item<VRecord>* CopyFirst = pGList->CopyDataList.getpHead();
            L1Item<VRecord>* CopyPre =NULL;
            while (CopyFirst!= NULL){
                t++;
                tempID=(string)CopyFirst->data.id;
                if (tempID==rID){
                    if (t==1){
                        pGList->CopyDataList.removeHead();
                    }
                    else{
                        CopyPre->pNext=CopyFirst->pNext;
                        delete CopyFirst;
                    }
                }
                CopyPre = CopyFirst;
                CopyFirst=CopyFirst->pNext;
            }
            if (!flag){
                cout<<y;
                cout<<": Failed";
                cout<<endl;
            }
            break;
        }                  // RVR
    }
    return true;
}


