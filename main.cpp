//#include <bits/stdc++.h>
#include <iostream>
#include <exception>
#include <memory>
#include <vector>

class Invalid : public std::exception {
public:
    Invalid() = default;

    const char *what() const noexcept override {
        return "Azi nu ne place numarul 13 pentru ca asa a zis Raluca!\n";
    }
};

class Nod
{
public:
    int info;
    Nod* next;

    //constructori
    Nod()
    {
        info = 0;
        next = NULL;
    }
    Nod(int info)
    {
        if(info==13)
            throw Invalid();
        this->info = info;
        this->next = NULL;
    }

    virtual ~Nod() { delete next; }

    friend std::ostream &operator<<(std::ostream &os, const Nod &nod) {
        os << nod.info<< " ";
        return os;
    }

    int getInfo() const {
        return info;
    }

    void setInfo(int info) {
        Nod::info = info;
    }
};

class Nod_dublu : public Nod
{
public:
    Nod_dublu *ante;
    Nod_dublu *next;

    Nod_dublu() : Nod() {};
    Nod_dublu(int info) : Nod(info)
    {
        this->next = NULL;
        this->ante = NULL;
    }
    virtual ~Nod_dublu()
    {
        delete next;
        delete ante;
    }

    //constructor de copiere
    Nod_dublu(const Nod_dublu &nodd){
        std::cout<<"Apel cc";
        this->info=nodd.info;
        this->next=nodd.next;
        this->ante=nodd.ante;
    }

    //reasignare pe =
    Nod_dublu& operator=(const Nod_dublu &nodd){
        std::cout<<"Apel pe egal";
        this->info=nodd.info;
        this->next=nodd.next;
        this->ante=nodd.ante;
        return *this;
    }

};

class LDI
{
public:
    Nod_dublu *head;

    LDI() { head = NULL;}
    virtual ~LDI()
    {
        Nod_dublu *nodd = head;

        while (nodd)
        {
            Nod_dublu* next = nodd->next;
            delete nodd;
            nodd = next;
        }
    };
    //restul funnctiilor
    virtual void insertFront(Nod_dublu**, int) const;
    virtual void insertEnd(Nod_dublu**, int) const;
    virtual void insertion(Nod_dublu**) const;
    virtual void swapInfo(Nod_dublu**,Nod_dublu**) const;
    //void test(Nod_dublu **);
    virtual void printList() const;

    friend std::ostream &operator<<(std::ostream &os, const LDI &ldi);

};

std::ostream &operator<<(std::ostream &os, const LDI &ldi) {
    os << "elem listei: ";
    ldi.printList();
    return os;
}

void LDI::insertFront(Nod_dublu **head, int info) const{
    Nod_dublu* newNode = new Nod_dublu(info);
    if (*head == NULL) {
        newNode->ante = NULL;
        newNode->next= NULL;
        *head = newNode;
    }
    else {
        newNode->next = *head;
        newNode->ante = NULL;
        *head = newNode;
    }
}

void LDI::insertEnd(Nod_dublu **head, int info) const{
    Nod_dublu* newNode = new Nod_dublu(info);
    if (*head == NULL) {
        newNode->ante = NULL;
        *head = newNode;
    }
    Nod_dublu* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->ante = temp;
    newNode->next = NULL;
}

void LDI::swapInfo(Nod_dublu **b, Nod_dublu **c)const{
    int aux=(*b)->info;
    (*b)->info=(*c)->info;
    (*c)->info=aux;
}

void LDI::insertion(Nod_dublu **head)const{
    Nod_dublu *a = this->head;
    Nod_dublu *b;
    while (a->next != NULL )
    {
        b = a->next; //nu se atribuie b->ante ptr a=head
        b->ante=a;  //nu merge fara asta
        while (b != NULL &&
               b->ante != NULL &&
               b->info < b->ante->info)
        {
            swapInfo(&b, &b->ante);
            b = b->ante;
        }
        a = a->next;
    }
}

void LDI::printList() const
{
    Nod_dublu *nod = head;

    if (head == NULL)
        std::cout << "Lista e goala." << std::endl;

    while (nod != NULL) {
        std::cout << nod->info << " ";
        nod = nod->next;
    }
    std::cout<<std::endl;
}

//LSI CREEAT CU SMART POINTERS
class LSII {
public:

    static std::vector<std::shared_ptr<Nod>> listasmart;

    LSII() = delete;

    static const std::vector<std::shared_ptr<Nod>> &getsmart() {
        return listasmart;
    }

    static void InsertSmart(const std::shared_ptr<Nod> &pr) {
        listasmart.push_back(pr);
    }

    static void printSmart() {

        std::cout << "\nelementele listei smart sunt: ";
        for (auto &nod: listasmart)
            std::cout << *nod << " ";
    };

};

class LSI : public LDI {
    public:
        Nod_dublu *head; //folosesc nod dublu ptr inheritance

        LSI() : LDI() { head = NULL; };

        virtual ~LSI() {};

        //restul funnctiilor
        void insertEnd(Nod_dublu **, int) const override;

        virtual void printList() { LDI::printList(); };
    };

    void LSI::insertEnd(Nod_dublu **head, int info) const {
        //nu merge totusi
        Nod_dublu *newNode = new Nod_dublu(info);
        if (*head == NULL)
            *head = newNode;
        Nod_dublu *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = NULL;

        //std::cout<<temp->info<<" ";
    }


    std::vector<std::shared_ptr<Nod>> LSII::listasmart;

    int main() {
        //mai multe apelari diverse ptr testare cod
        LDI l;
        LSI s;
        //nu merge afisarea lui s:((((
        s.printList();
        s.insertEnd(&s.head, 5);
        s.insertEnd(&s.head, 6);
        s.insertEnd(&s.head, 7);
        s.insertEnd(&s.head, 8);

        l.insertFront(&l.head, 1);
        l.insertFront(&l.head, 5);
        l.insertFront(&l.head, 6);
        l.insertEnd(&l.head, 2);
        l.insertEnd(&l.head, 4);
        l.insertEnd(&l.head, 3);

        l.printList();
        l.insertion(&l.head);
        std::cout<<"lista dupa InsertionSort:";
        l.printList();

        Nod_dublu n(7);
        Nod_dublu no = n;
        std::cout << std::endl << n.info << no.info; //77
        Nod nn(10);

        std::cout << std::endl << nn;     //std::cout la nod
        std::cout << std::endl << l;      //std::cout la LDI
        //std::cout << std::endl << s;      //std::cout la LSI -> nu merge

        try {
            Nod_dublu inv(13);
        }
        catch (const Invalid &e) {
            std::cout << e.what();
        };

        //lista simplu inlantuita folosind smart pointers

        auto a = std:: make_shared<Nod>(200);
        auto b = std:: make_shared<Nod>(210);
        auto c = std:: make_shared<Nod>(220);
        auto d = std:: make_shared<Nod>(230);
        LSII::InsertSmart(a);
        LSII::InsertSmart(b);
        LSII::InsertSmart(c);
        LSII::InsertSmart(d);

        LSII::printSmart();
        return 0;
    }
