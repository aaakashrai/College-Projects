#include <bits/stdc++.h >
using namespace std;
typedef unsigned long long int ll;
class process {
        public:
        string name;
        int pid;
        int user;
        int pr;
        process(string s, int p, int u, int prio) {
                name = s;
                pid = p;
                user = u;
                pr = prio;
        }
        void operator = (const process * D) {
                name = D -> name;
                pid = D -> pid;
                user = D -> user;
                pr = D -> pr;
        }
};

//====================================================================

template < class T >
        class pq {
          public:
                T * list[100];
                int size;

                        pq() {
                                size = -1;
                                for (int i = 0; i < 100; i++)
                                        list[i] = NULL;
                        }
                void heapify() {
                        for (int i = (size - 1) / 2; i >= 0; i--) {
                                int l = i * 2 + 1;
                                int r = i * 2 + 2;
                                int max = i;
                                if (l <= size && list[l] -> pr > list[i] -> pr)
                                        max = l;
                                if (r <= size && list[l] -> pr > list[max] -> pr)
                                        max = r;
                                T * te = list[i];
                                list[i] = list[max];
                                list[max] = te;
                        }
                }
                void maxheapify(int i) {
                        if (i < 0)
                                return;
                        int l = i * 2 + 1;
                        int r = i * 2 + 2;
                        int max = i;
                        if (l <= size && list[l] -> pr > list[i] -> pr)
                                max = l;
                        if (r <= size && list[l] -> pr > list[max] -> pr)
                                max = r;
                        if (max != i) {
                                T * te = list[i];
                                list[i] = list[max];
                                list[max] = te;
                                maxheapify(max);
                        }
                }

                void endproc(string s) {
                        int loc = -1;
                        for (int i = 0; i <= size; i++) {
                                if (list[i] -> name == s) {
                                        loc = i;
                                        break;
                                }
                        }
                        if (loc == -1)
                                cout << "No such process exists\n";
                        T * te = list[size];
                        list[size] = list[loc];
                        list[loc] = te;
                        size--;
                        maxheapify(loc);
                }

                void endproc() {
                        int loc = 0;
                        if (size== -1)
                                cout << "No process exists\n";
                        T * te = list[size];
                        list[size] = list[loc];
                        list[loc] = te;
                        size--;
                        maxheapify(loc);
                }


                void addproc(T * prr) {
                        size++;
                        list[size] = prr;
                        maxheapify((size - 1) / 2);
                }

                void dis() {
                        if (size == -1) {
                                cout << "NO process" << endl;
                                return;
                        }
                        for (int i = 0; i <= size; i++)
                                cout << list[i] -> name << "  " << list[i] -> pr << endl;
                }
        };
//====================================================================

class Tnode {
        public:
                Tnode * list[26];
                bool isend;

        Tnode() {
                for (int i = 0; i < 26; i++)
                        list[i] = NULL;
                isend = false;
        }
};

//====================================================

class commandlist {
        Tnode * head;
        public:
                commandlist() {
                        head = new Tnode;
                }
        void inser(string s, Tnode * p, int loc) {
                int len = s.size();
                if (loc >= len) {
                        p -> isend = true;
                        return;
                }
                Tnode * temp = p;
                char ele = s[loc];
                int ind = ele - 'a';
                if (temp -> list[ind] == NULL)
                        temp -> list[ind] = new Tnode();
                temp = temp -> list[ind];
                inser(s, temp, loc + 1);
        }

        void disp(Tnode * p, string s) {
                if (p -> isend == true)
                        cout << s << endl;
                for (int i = 0; i < 26; i++) {
                        if (p -> list[i] != NULL)
                                disp(p -> list[i], s + char(i + 'a'));
                }
        }

        Tnode * search(string s, int loc, Tnode * t) {
                int len = s.size();
                if (len == loc)
                        return t;
                char d = s[loc];
                int ind = d - 'a';
                if (t -> list[ind] == NULL)
                        return NULL;
                else
                        return search(s, loc + 1, t -> list[ind]);
        }

        void searchit(string s) {
                Tnode * d = search(s, 0, head);
                if (d == NULL)
                        cout << "NO match";
                else
                        disp(d, s);
        }

        void startdisp() {
                disp(head, "");
        }

        void startinsertion(string s) {
                inser(s, head, 0);
        }
};
//====================================================================


class Fnode{
public:
  string name;
  Fnode *list[100];
  int size;
  Fnode *parent;
  Fnode(string n, Fnode *p)
  {
    name= n;
    for(int i=0;i<100;i++)
    list[i]=NULL;
    size= -1;
    parent =p;
  }
  Fnode(string n)
  {
    name= n;
    for(int i=0;i<100;i++)
    list[i]=NULL;
    size= -1;
    parent =NULL;
  }
};
//=====================================================================

class Directory{
public:
  Fnode *root;
  Directory()
  {
    root= new Fnode("root");
    root->parent = root;
  }
  void adddir(string name, Fnode *p)
  {
    p->list[++(p->size)]= new Fnode(name, p);
  }
  void removedir(string s, Fnode *p)
  {
    int loc= -1;
    for(int i=0;i<=(p->size);i++)
    {
      if(p->list[i]->name == s){
        loc= i;
        break;
      }
    }
    if(loc== -1)
    {
      cout << "No such directory.\n";
      return;
    }
    p->list[loc]= p->list[(p->size)--];
  }

  void listdir(Fnode *p)
  {
    for(int i=0;i<=(p->size);i++)
    cout << "\\" << p->list[i]->name << '\t' ;
    cout << endl;
  }


};

//====================================================================

class terminal {
        bool isroot;
        int userid;
        commandlist cl;
        int processno;
        pq <process> prq;
        public:
          Fnode *currdirectory;
          Directory dir;
          terminal()
          {
                  currdirectory= dir.root;
                  isroot = false;
                  userid=0;
                  processno= 1;
          }
        void addcommand(string s) {
                cl.startinsertion(s);

        }

        void htop()
        {
            cout << "=========================================================\n";
            cout << "|     Name          pid         user         priority   |\n";
            cout << "=========================================================\n";
            int len= prq.size;
            for(int i=0;i<=len;i++)
            cout <<setw(12) << prq.list[i]->name <<setw(12) << prq.list[i]->pid << setw(12) << prq.list[i]->user << setw(12) << prq.list[i]->pr << '\n' ;
        }


        void init() {
                cout << "\n\n\n\n\n\n\n\n";
                cout << "\t _       __     __                             __           ______          ___               " << endl;
                cout << "\t| |     / ___  / _________  ____ ___  ___     / /_____     / ________  ____/ (___  ______ ___ " << endl;
                cout << "\t| | /| / / _\\/ / ___/ __ \\/ __ `__ \\/ _ \\   / __/ __ \\   / /   / __ \\/ __  / / / / / __ `__ \\" << endl;
                cout << "\t| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /_/ /_/ /  / /___/ /_/ / /_/ / / /_/ / / / / / /" << endl;
                cout << "\t|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/   \\__/\\____/   \\____/\\____/\\__,_/_/\\__,_/_/ /_/ /_/ " << endl;
                cout << "\n\n \t\t\t\t\t\tPLEASE WAIT WHILE WE LOAD";
                cout << "\n\n\n\n\t\t\t";

                time_t curr_time = time(NULL);
                time_t limit = curr_time + 1;
                for (int i = 0; i < 10; i++) {
                        int done = 0;
                        while (curr_time < limit) {
                                if (done == 0)
                                        cout << "*******";
                                curr_time = time(NULL);
                                done = 1;
                        }
                        limit++;
                }
                cout << "\n\n\n";
                cout << "Enter your username followed by your password\n";
                string s, p;
                int tries = 0;
                bool access = false;
                while (tries < 3) {
                        cin >> s >> p;
                        if (valid(s, p)) {
                                access = true;
                                if (s == "root")
                                        isroot = true;
                                if (s == "root")
                                        userid = 1;
                                else
                                        userid = 2;
                                break;
                        } else
                                cout << "Wrong username or password\n";
                        tries++;
                }
                if (tries == 3 && access == false) {
                        cout << "Too many wrong attempts! exiting\n";
                        curr_time = time(NULL);
                        limit = curr_time + 1;
                        while (curr_time < limit)
                                curr_time = time(NULL);
                        exit(0);
                }
                if (access == true) {
                        system("CLS");
                        cout << "Login Successful\n";
                        cout << "type help for info about commands.\n";
                        dir.adddir("boot",currdirectory);
                        dir.adddir("etc",currdirectory);
                        dir.adddir("home",currdirectory);
                        dir.adddir("bin",currdirectory);
                        dir.adddir("usr",currdirectory);
                        dir.adddir("tmp",currdirectory);
                        dir.adddir("Desktop",currdirectory->list[2]);
                        dir.adddir("Music",currdirectory->list[2]);
                        dir.adddir("Videos",currdirectory->list[2]);
                        dir.adddir("Documents",currdirectory->list[2]);
                        cl.startinsertion("htop");
                        cl.startinsertion("exit");
                        cl.startinsertion("logout");
                        cl.startinsertion("adduser");
                        cl.startinsertion("cd");
                        cl.startinsertion("ls");
                        cl.startinsertion("rm");
                        cl.startinsertion("pwd");
                        cl.startinsertion("ad");
                        cl.startinsertion("addcmd");
                        cl.startinsertion("predict");
                        cl.startinsertion("addpr");
                        cl.startinsertion("killpr");
                        cl.startinsertion("killwpr");
                        process *t= new process("system", processno, userid, 15);
                        prq.addproc(t);
                        processno++;
                        t = new process("diskmanager", processno, userid, 10);
                         prq.addproc(t);
                        processno++;
                         t= new process("access", processno, userid, 9);
                         prq.addproc(t);
                        processno++;
                         t= new process("services", processno, userid, 3);
                         prq.addproc(t);
                        processno++;
                }
        }

        void help()
        {
                cout << "Various commands are\n";
                cout << "htop: list various processes running\n";
                cout << "exit: Exit the terminal.\n";
                cout << "logout: logs out the user to the beginning screen.\n";
                cout << "adduser: Allows root to add new users to the system.\n";
                cout << "cd: changes working path to a new directory.\n";
                cout << "ls: list the content of current directory\n";
                cout << "rm: remove a directory\n";
                cout << "pwd: prints the currently working directory\n";
                cout << "ad: adds a new directory\n";
                cout << "addcmd: add a new command to list.\n";
                cout << "predict: predicts available commands matching your string.\n";
                cout << "addpr: add a new process. You must also provide a priority ranging from 1 to 20.\n";
                cout << "killwpr: kill the app with most priority.\n";
                cout << "killpr: kill the specified process.\n";
        }

        void changedir(string s)
        {
          if(s== ".."){
          currdirectory = currdirectory->parent;
          return;
        }
          int loc= -1;
          for(int i=0;i<= currdirectory->size;i++)
          {
            if(currdirectory->list[i]->name == s)
            {
              loc=i;
              break;
            }
            //cout << currdirectory->list[i]->name << ' ' << s << endl;
          }
          if(loc== -1)
          {
            cout << "No such directory exists.\n" ;
            return;
          }
          currdirectory= currdirectory->list[loc];
          cout << "Directory successfully changed.\n";
        }

        void showcurrdir()
        {
          cout << currdirectory->name << endl;
        }

        void predicts(string s)
        {
          cl.searchit(s);
        }
        void remdir(string s)
        {
          dir.removedir(s, currdirectory);
        }

        void addprocess(string s, int pr)
        {
          process *t = new process(s, processno, userid, pr);
          prq.addproc(t);
          processno++;
        }
        void add(string s)
        {
          dir.adddir(s, currdirectory);
        }

        void killpr(string s)
        {
          prq.endproc(s);
        }

        void killwpr()
        {
          prq.endproc();
        }
        void showdir()
        {
          dir.listdir(currdirectory);
        }
        void addusr() {
                if (isroot == false)
                        cout << "Cannot add a user unless you are root. Please restart and login as root.\n";
                else {
                        string s, p, p1;
                        cout << "Enter new user's name.\n";
                        cin >> s;
                        cout << "Enter new user's password\n";
                        cin >> p;
                        cout << "Renter new user's password\n";
                        cin >> p1;
                        if (p != p1) {
                                cout << "Passwords dont match. Try again.\n";
                                return;
                        }
                        ll val = hasher(s, p);
                        ofstream myfile("myfile.txt",std::ios_base::app);
                        if (myfile.is_open()) {
                                myfile << "\n" << val << "\n";
                                myfile.close();
                        }
                }
        }

        void logout() {
                isroot = false;
                system("CLS");
                init();
        }

        bool valid(string s, string p) {
                string line;
                ll check = hasher(s, p);
                ll val;
                ifstream myfile("myfile.txt");
                if (myfile.is_open()) {
                        while (getline(myfile, line)) {
                                stringstream geek(line);
                                geek >> val;
                                if (val == check)
                                        return true;
                        }
                        myfile.close();
                } else
                        cout << "NOT OPEN";
                return false;
        }

        ll hasher(string s, string p) {
                string t = s + p;
                ll val = 0;
                int len = t.size();
                for (int i = 0; i < len; i++) {
                        val += i * int(t[i]);
                }
                val = val * val + 3 * val - 12;
                return val;
        }
};

//====================================================================
int main() {
        terminal t;
        t.init();
        while (1) {
          cout << ">>>   ";
                string s;
                cin >> s;
                if (s == "exit")
                        exit(0);
                else if (s == "clr"){
                        system("CLS");
                        cout << "type help for info about commands.\n";
                      }
                else if (s == "adduser") {
                        t.addusr();
                }
                else if (s == "logout") {
                        t.logout();
                }
                else if(s=="cd")
                {
                  string p;
                  cin >> p;
                  t.changedir(p);
                }
                else if(s=="pwd")
                {
                  t.showcurrdir();
                }
                else if(s=="rm")
                {
                  string p;
                  cin >> p;
                  t.remdir(p);
                }
                else if(s== "help")
                  t.help();
                else if(s== "ls")
                  t.showdir();
                else if(s== "ad")
                {
                  string p;
                  cin >> p;
                  t.add(p);
                }
                else if(s== "addcmd")
                {
                  string p;
                  cin >> p;
                  t.addcommand(p);
                  cout << "Command Added Successfully.\n";
                }
                else if(s== "predict")
                {
                  string p;
                  cin >> p;
                  t.predicts(p);
                }
                else if(s== "htop")
                {
                  t.htop();
                }
                else if(s== "addpr")
                {
                  string p;
                  int c;
                  cin >> p >> c;
                  t.addprocess(p,c);
                  cout << "Process Added Successfully.\n";
                }
                else if(s== "killpr")
                {
                  string p;
                  cin >> p;
                  t.killpr(p);
                  cout << "Process Killed Successfully.\n";
                }
                else if(s== "killwpr")
                {
                  t.killwpr();
                  cout << "Process Killed Successfully.\n";
                }
                else
                cout << "Not a valid command.\n";
        }
}
