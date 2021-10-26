#include "EmployeeDirectory.hpp"

// [HELPER FUNCTIONS]
char EmployeeDirectory::getLastInitial(string name) {
    int found_ix = name.find(' ');

    if (found_ix != string::npos)
        return name[found_ix + 1];

    return '\0';
}

void EmployeeDirectory::printEmployee(LLNode* n) {
    if (n == NULL) {
        cout << "LLNode is NULL." << endl;
    }
    else {
        cout << "Employee Information" << endl;
        cout << "====================" << endl;
        cout << "ID     : " << n->empId << endl;
        cout << "Name   : " << n->empName << endl;
        cout << "Level  : " << n->empLevel << endl;
        cout << "Phone  : " << n->empPhone << endl;
        cout << "Joined : " << n->empJoiningYear << endl;
    }
}


// [TO BE IMPLEMENTED]
// ----------------------------------------------------------------------------

EmployeeDirectory::EmployeeDirectory() {
    root=NULL;
}

// ----------------------------------------------------------------------------

EmployeeDirectory::~EmployeeDirectory() {
    // TODO
}

// ----------------------------------------------------------------------------

TreeNode* AuxiliarSearchChar(TreeNode* traveler, char key)
{
    if (traveler==NULL)
    {
        return NULL;
    }
    if (traveler->lastInitial==key)
    {
        return traveler;
    }
    if (traveler->lastInitial>key)
    {
        return AuxiliarSearchChar(traveler->left,key);
    }
    return AuxiliarSearchChar(traveler->right,key);
    
}

TreeNode* EmployeeDirectory::searchCharNode(char key) 
{
    AuxiliarSearchChar(root,key);
}

// ----------------------------------------------------------------------------

void showEmployeeAuxiliar(TreeNode* traveler)
{

    if (traveler==NULL)
    {
        return;
    }
    showEmployeeAuxiliar(traveler->left);
    if (traveler->parent==NULL)
    {
        cout<<"[Employees with lastInitial="<<traveler->lastInitial<<", parent= "<<"]"<<endl;
        LLNode* travelman=traveler->head;
        if (travelman!=NULL)
        {
            while(travelman!=NULL)
            {
                cout<<"> "<<travelman->empName <<", "<< travelman->empPhone<<", "<< travelman->empId<<endl;
                travelman=travelman->next;
            }
        }
        else
        {
            cout<<"No employees found."<<endl;
        }
        cout<<"---------------------------------------"<<endl;
    }
    else
    {
        cout<<"[Employees with lastInitial="<<traveler->lastInitial<<", parent="<<traveler->parent->lastInitial<<"]"<<endl;
        LLNode* travelman=traveler->head;
        if (travelman!=NULL)
        {
            while(travelman!=NULL)
            {
                cout<<"> "<<travelman->empName <<", "<< travelman->empPhone<<", "<< travelman->empId<<endl;
                travelman=travelman->next;
            }
        }
        else
        {
            cout<<"No employees found."<<endl;
        }
        cout<<"---------------------------------------"<<endl;
    }

    showEmployeeAuxiliar(traveler->right);
}

void EmployeeDirectory::showEmployeeDirectory() 
{
    showEmployeeAuxiliar(root);
}

// ----------------------------------------------------------------------------

LLNode* SearchEmployeeLLAuxiliar(int id, string name, LLNode* traveler)
{
    while (traveler!=NULL)
    {
        if (id==traveler->empId&&name==traveler->empName)
        {
            return traveler;
        }
        traveler=traveler->next;
    }
    return NULL;
}

LLNode* EmployeeDirectory::searchEmployee(int empId, string empName) 
{
    char helper= getLastInitial(empName);
    TreeNode* PositionOnTree = searchCharNode(helper);
    LLNode* employeefound= SearchEmployeeLLAuxiliar(empId,empName,PositionOnTree->head);
    return employeefound;
    
}

// ----------------------------------------------------------------------------
void LLauxiliarinsertnew(int empid, string name, int lvl, string phone,int year,TreeNode* treeposition)
{
    LLNode* traveler=treeposition->head;
    LLNode* traveler2=treeposition->head;
    if(traveler==NULL)
    {
        traveler=new LLNode(empid,name,lvl,phone,year);
        treeposition->head=traveler;
        treeposition->head->next=NULL;
        return;
    }
    else if(treeposition->head->next==NULL)
    {
        if (treeposition->head->empId < empid )
        {
            LLNode* newracoon= new LLNode(empid,name,lvl,phone,year);
            traveler->next= newracoon;
        }
        else if(treeposition->head->empId>empid)
        {
            LLNode* newracoon= new LLNode(empid,name,lvl,phone,year);
            newracoon->next= treeposition->head;
            treeposition->head=newracoon;
        }
        return;
    }
    else
    {  
        while ( traveler!=NULL && traveler->empId<empid )
        {
            traveler=traveler->next;
        }
        while (traveler2!=NULL&&traveler2->next!=traveler)
        {
            traveler2=traveler2->next;
        }
        LLNode* newracoon= new LLNode(empid,name,lvl,phone,year);
        newracoon->next=traveler;
        traveler2->next=newracoon;
        
    }


}

TreeNode* CreateTreeNodeAux(char data, TreeNode* parent)
{
    TreeNode* addnode= new TreeNode(data);
    addnode->head=NULL;
    addnode->left=NULL;
    addnode->right=NULL;
    addnode->parent= parent;
    return addnode;

}

TreeNode* addingTreenodeAuxiliar(TreeNode* traveler,char initial,TreeNode* parenthelper)
{
    if (traveler==NULL)
    {
        return CreateTreeNodeAux(initial,parenthelper);
    }
    else if(traveler->lastInitial<initial)
    {
        traveler->right=addingTreenodeAuxiliar(traveler->right,initial,traveler);
    }
    else if(traveler->lastInitial>initial)
    {
        traveler->left=addingTreenodeAuxiliar(traveler->left,initial,traveler);
    }
    return traveler;

}


void EmployeeDirectory::insertEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear)
{
    char initial= getLastInitial(empName);
    TreeNode* Wonderer = searchCharNode(initial);
    if(root==NULL)
    {
        root= CreateTreeNodeAux(initial,NULL);
        LLauxiliarinsertnew(empId,empName,empLevel,empPhone,empJoiningYear,root);
        return;
    }
    else if (Wonderer==NULL)
    {
        root = addingTreenodeAuxiliar(root,initial,NULL);
        Wonderer=searchCharNode(initial);
        LLauxiliarinsertnew(empId,empName,empLevel,empPhone,empJoiningYear,Wonderer);

    }else
    {
        LLauxiliarinsertnew(empId,empName,empLevel,empPhone,empJoiningYear,Wonderer);
    }
    
}

// ----------------------------------------------------------------------------

void EmployeeDirectory::removeEmployee(int empId, string empName) {
    // TODO
}

// ----------------------------------------------------------------------------

void EmployeeDirectory::leftRotate(TreeNode* curr) {
    // TODO
}

// ----------------------------------------------------------------------------
