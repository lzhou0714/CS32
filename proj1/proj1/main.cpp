// garks.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "Gark.h"
#include "Player.h"
#include "Mesa.h"
//#include "globals.h"
#include "Game.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//  Mesa implementations
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

class StreambufSwitcher
{
    public:
        StreambufSwitcher(ios& dest, streambuf* sb,
                                        ios::iostate exceptions = ios::goodbit)
         : dest_stream(dest), oldsb(dest.rdbuf(sb)), oldex(dest.exceptions())
        { dest_stream.exceptions(exceptions); }
        StreambufSwitcher(ios& dest, ios& src)
         : StreambufSwitcher(dest, src.rdbuf(), src.exceptions())
        {}
        ~StreambufSwitcher()
        { dest_stream.rdbuf(oldsb); dest_stream.exceptions(oldex); }
    private:
        ios& dest_stream;
        streambuf* oldsb;
        ios::iostate oldex;
};

map<void*, size_t> allocMap;
bool recordaddrs = false;

inline bool isRecordedSize(size_t n)
{
        return n == sizeof(Gark)  ||  n == sizeof(Player);
}

void* operator new(size_t n)
{
        void* p = malloc(n);
        fill_n(static_cast<char*>(p), n, 0xca);
        if (recordaddrs  &&  isRecordedSize(n))
        {
                recordaddrs = false;
                allocMap.insert(make_pair(p, n));
                recordaddrs = true;
        }
        return p;
}

void unrecordaddr(void* p)
{
        recordaddrs = false;
        auto it = allocMap.find(p);
        if (it != allocMap.end())
        {
                fill_n(static_cast<char*>(p), it->second, 0xcb);
                allocMap.erase(it);
        }
        recordaddrs = true;
}

#if __cplusplus >= 201402L  &&  ! defined(__clang__)
// Unless clang is supplied the -fsized-deallocation flag, it will
// not call the C++14/17 sized operator delete.

void operator delete(void* p) noexcept
{
        free(p);
}

void operator delete(void* p, size_t n) noexcept
{
        if (recordaddrs  &&  isRecordedSize(n))
                unrecordaddr(p);
        operator delete(p);
}
#else
void operator delete(void* p) noexcept
{
        if (recordaddrs)
                unrecordaddr(p);
        free(p);
}
#endif

void testone(int n)
{
        StreambufSwitcher sso(cout, cerr);

        switch (n)
        {
                                 default: {
                cout << "Bad argument" << endl;
                        } break; case  1: {
                Mesa m(15, 18);
                m.addPlayer(2, 2);
                Gark g(&m, 5, 17);
                assert(g.row() == 5  &&  g.col() == 17);
                        } break; case  2: {
                Mesa m(20, 25);
                m.addPlayer(1, 1);
                Gark g(&m, 12, 17);
                for (int k = 0; k < 8; k++)
                {
                        int oldr = g.row();
                        int oldc = g.col();
                        g.move();
                        assert((g.row() == oldr  &&  abs(g.col() - oldc) == 1)  ||
                               (g.col() == oldc  &&  abs(g.row() - oldr) == 1));
                }
                        } break; case  3: {
                bool moved = false;
                for (int k = 0; k < 50; k++)
                {
                        Mesa m(1, 24);
                        m.addPlayer(1, 1);
                        Gark g(&m, 1, 24);
                        for (int m = 0; m < 20  &&  g.col() > 1; m++)
                        {
                                int oldc = g.col();
                                g.move();
                                assert(g.row() == 1  &&  g.col() <= 24  &&
                                                abs(g.col() - oldc) <= 1);
                                if (g.col() != oldc)
                                        moved = true;
                        }
                }
                assert(moved);
                        } break; case  4: {
                bool moved = false;
                for (int k = 0; k < 50; k++)
                {
                        Mesa m(19, 1);
                        m.addPlayer(1, 1);
                        Gark g(&m, 19, 1);
                        for (int m = 0; m < 17  &&  g.row() > 1; m++)
                        {
                                int oldr = g.row();
                                g.move();
                                assert(g.col() == 1  &&  g.row() <= 19  &&
                                                abs(g.row() - oldr) <= 1);
                                if (g.row() != oldr)
                                        moved = true;
                        }
                }
                assert(moved);
                        } break; case  5: {
                bool moved = false;
                for (int k = 0; k < 50; k++)
                {
                        Mesa m(1, 25);
                        m.addPlayer(1, 25);
                        Gark g(&m, 1, 1);
                        for (int m = 0; m < 20  &&  g.col() < 25; m++)
                        {
                                int oldc = g.col();
                                g.move();
                                assert(g.row() == 1  &&  g.col() >= 1  &&
                                                abs(g.col() - oldc) <= 1);
                                if (g.col() != oldc)
                                        moved = true;
                        }
                }
                assert(moved);
                        } break; case  6: {
                bool moved = false;
                for (int k = 0; k < 50; k++)
                {
                        Mesa m(20, 1);
                        m.addPlayer(20, 1);
                        Gark g(&m, 1, 1);
                        for (int m = 0; m < 20  &&  g.row() < 20 ; m++)
                        {
                                int oldr = g.row();
                                g.move();
                                assert(g.col() == 1  &&  g.row() >= 1  &&
                                                abs(g.row() - oldr) <= 1);
                                if (g.row() != oldr)
                                        moved = true;
                        }
                }
                assert(moved);
                        } break; case  7: {
                Mesa m(10, 20);
                m.addPlayer(1, 1);
                Gark g(&m, 8, 12);
                g.move();
                assert((g.row() == 8  &&  abs(g.col() - 12) == 1)  ||
                       (g.col() == 12  &&  abs(g.row() - 8) == 1));

                        } break; case  8: {
                Mesa m(10, 20);
                m.addPlayer(1, 1);
                Gark g(&m, 5, 7);
                assert(!g.getAttacked(UP));
                assert(g.getAttacked(DOWN));
                        } break; case  9: {
                Mesa m(10, 20);
                m.addPlayer(1, 1);
                Gark g(&m, 5, 1);
                assert(g.getAttacked(LEFT));
                        } break; case 10: {
                Mesa m(10, 20);
                Player p(&m, 2, 3);
                assert(p.row() == 2  &&  p.col() == 3);
                        } break; case 11: {
                Mesa m(10, 20);
                Player p(&m, 2, 3);
                assert(!p.isDead());
                p.setDead();
                assert(p.isDead());
                        } break; case 12: {
                Mesa m(10, 20);
                m.addPlayer(8, 12);
                Player* p = m.player();
                p->moveOrAttack(UP);
                assert(p->row() == 7  &&  p->col() == 12);
                p->moveOrAttack(DOWN);
                assert(p->row() == 8  &&  p->col() == 12);
                p->moveOrAttack(LEFT);
                assert(p->row() == 8  &&  p->col() == 11);
                p->moveOrAttack(RIGHT);
                assert(p->row() == 8  &&  p->col() == 12);
                        } break; case 13: {
                Mesa m(15, 18);
                m.addPlayer(1, 1);
                Player* p = m.player();
                p->moveOrAttack(LEFT);
                assert(p->row() == 1  &&  p->col() == 1  &&  !p->isDead());
                p->moveOrAttack(UP);
                assert(p->row() == 1  &&  p->col() == 1  &&  !p->isDead());
                        } break; case 14: {
                Mesa m(15, 18);
                m.addPlayer(15, 18);
                Player* p = m.player();
                p->moveOrAttack(RIGHT);
                assert(p->row() == 15  &&  p->col() == 18  &&  !p->isDead());
                p->moveOrAttack(DOWN);
                assert(p->row() == 15  &&  p->col() == 18  &&  !p->isDead());
                        } break; case 15: {
                Mesa m(10, 20);
                m.addPlayer(5, 6);
                m.addGark(5, 7);
                assert(m.numGarksAt(5, 7) == 1  &&  m.numGarksAt(5, 8) == 0);
                Player* p = m.player();
                p->moveOrAttack(RIGHT);
                assert(p->row() == 5  &&  p->col() == 6  &&
                        m.numGarksAt(5, 7) == 0  &&  m.numGarksAt(5, 8) == 1);
                        } break; case 16: {
                Mesa m(10, 20);
                m.addPlayer(5, 6);
                m.addGark(5, 7);
                assert(m.numGarksAt(5, 7) == 1  &&  m.numGarksAt(5, 8) == 0);
                Player* p = m.player();
                p->moveOrAttack(RIGHT);
                assert(p->row() == 5  &&  p->col() == 6  &&
                        m.numGarksAt(5, 7) == 0  &&  m.numGarksAt(5, 8) == 1);
                p->moveOrAttack(RIGHT);
                assert(p->row() == 5  &&  p->col() == 7  &&
                        m.numGarksAt(5, 7) == 0  &&  m.numGarksAt(5, 8) == 1);
                p->moveOrAttack(RIGHT);
                assert(p->row() == 5  &&  p->col() == 7  &&
                        m.numGarksAt(5, 7) == 0  &&  m.numGarksAt(5, 8) == 0);
                        } break; case 17: {
                Mesa m(19, 22);
                assert(m.rows() == 19  &&  m.cols() == 22);
                        } break; case 18: {
                Mesa m(10, 20);
                m.addPlayer(3, 6);
                m.addGark(7, 5);
                m.addGark(4, 7);
                m.addGark(7, 5);
                assert(m.numGarksAt(7, 5) == 2  &&  m.garkCount() == 3);
                        } break; case 19: {
                Mesa m(10, 20);
                int r = 5;
                int c = 7;
                assert(m.determineNewPosition(r, c, UP)  &&  r == 4  &&  c == 7);
                assert(m.determineNewPosition(r, c, LEFT)  &&  r == 4  &&  c == 6);
                assert(m.determineNewPosition(r, c, DOWN)  &&  r == 5  &&  c == 6);
                assert(m.determineNewPosition(r, c, RIGHT)  &&  r == 5  &&  c == 7);
                        } break; case 20: {
                Mesa m(10, 20);
                int r = 1;
                int c = 7;
                assert(!m.determineNewPosition(r, c, UP)  &&  r == 1  &&  c == 7);
                r = 5;
                c = 1;
                assert(!m.determineNewPosition(r, c, LEFT)  &&  r == 5  &&  c == 1);
                        } break; case 21: {
                Mesa m(10, 20);
                int r = 10;
                int c = 7;
                assert(!m.determineNewPosition(r, c, DOWN)  &&  r == 10  &&  c == 7);
                r = 5;
                c = 20;
                assert(!m.determineNewPosition(r, c, RIGHT)  &&  r == 5  &&  c == 20);
                        } break; case 22: {
                Mesa m(10, 20);
                m.addPlayer(3, 6);
                m.addGark(4, 4);
                assert(!m.attackGarkAt(4, 5, RIGHT)  &&  m.numGarksAt(4, 4) == 1  &&
                        m.numGarksAt(4, 6) == 0  &&  m.garkCount() == 1);
                        } break; case 23: {
                Mesa m(10, 20);
                m.addPlayer(3, 6);
                m.addGark(4, 4);
                assert(m.numGarksAt(4, 4) == 1  &&  m.numGarksAt(5, 4) == 0  &&
                        m.garkCount() == 1);
                assert(!m.attackGarkAt(4, 4, DOWN));
                assert(m.numGarksAt(5, 4) == 1  &&  m.numGarksAt(4, 4) == 0  &&
                        m.garkCount() == 1);
                assert(m.attackGarkAt(5, 4, RIGHT));
                assert(m.numGarksAt(5, 4) == 0  &&  m.numGarksAt(5, 5) == 0  &&
                        m.garkCount() == 0);
                        } break; case 24: {
                Mesa m(10, 20);
                m.addPlayer(3, 6);
                m.addGark(4, 4);
                m.addGark(7, 5);
                m.addGark(5, 7);
                m.addGark(7, 5);
                int oldCount = m.garkCount();
                m.attackGarkAt(5, 7, LEFT);
                assert(m.numGarksAt(5, 6) == 1  &&  m.garkCount() == oldCount);
                m.attackGarkAt(4, 4, UP);
                assert(m.numGarksAt(5, 6) == 1  &&  m.garkCount() == oldCount);
                assert(m.numGarksAt(3, 4) == 1);
                m.attackGarkAt(5, 6, LEFT);
                assert(m.numGarksAt(5, 6) == 0  &&  m.numGarksAt(5, 5) == 0  &&
                        m.garkCount() == oldCount-1);
                assert(m.numGarksAt(3, 4) == 1);
                        } break; case 25: {
                Mesa m(10, 20);
                m.addPlayer(3, 6);
                m.addGark(4, 4);
                m.addGark(7, 5);
                m.addGark(8, 5);
                m.addGark(7, 5);
                int oldCount = m.garkCount();
                m.attackGarkAt(7, 5, DOWN);
                assert(m.numGarksAt(7, 5) == 1  &&  m.numGarksAt(8, 5) == 2  &&
                        m.garkCount() == oldCount);
                m.attackGarkAt(8, 5, DOWN);
                assert((m.numGarksAt(8, 5) == 1  &&  m.numGarksAt(9, 5) == 0  &&
                        m.garkCount() == oldCount-1)  ||
                       (m.numGarksAt(8, 5) == 1  &&  m.numGarksAt(9, 5) == 1  &&
                        m.garkCount() == oldCount));
                m.attackGarkAt(8, 5, DOWN);
                assert(m.numGarksAt(8, 5) == 0  &&  m.numGarksAt(9, 5) == 1  &&
                        m.garkCount() == oldCount-1);
                m.attackGarkAt(9, 5, DOWN);
                assert(m.numGarksAt(9, 5) == 0  &&  m.garkCount() == oldCount-2);
                        } break; case 26: {
                Mesa m(10, 20);
                m.addPlayer(6, 17);
                for (int r = 1; r <= 10; r++)
                        for (int c = 1; c <= 15; c++)
                                assert(m.addGark(r, c));
                assert(!m.addGark(5, 17));
                        } break; case 27: {
                Mesa m(10, 20);
                m.addPlayer(6, 6);
                m.addGark(4, 6);
                m.addGark(5, 8);
                m.moveGarks();
                assert(m.numGarksAt(4, 6) == 0  &&
                        (m.numGarksAt(3, 6) + m.numGarksAt(5, 6) +
                         m.numGarksAt(4, 5) + m.numGarksAt(4, 7)) == 1);
                assert(m.numGarksAt(5, 8) == 0  &&
                        (m.numGarksAt(4, 8) + m.numGarksAt(6, 8) +
                         m.numGarksAt(5, 7) + m.numGarksAt(5, 9)) == 1);
                        } break; case 28: {
                Mesa m(10, 20);
                m.addPlayer(7, 7);
                for (int k = 0; k < MAXGARKS/4; k++)
                {
                        m.addGark(6, 7);
                        m.addGark(8, 7);
                        m.addGark(7, 6);
                        m.addGark(7, 8);
                }
                assert( ! m.player()->isDead());
                m.moveGarks();
                assert(m.player()->isDead());
                        } break; case 29: {
                Mesa m(1, 3);
                m.addPlayer(1, 1);
                Player* p = m.player();
                for (int j = 0; j < 10; j++)
                        m.addGark(1, 3);
                assert(!p->isDead());
                m.moveGarks();
                int k;
                for (k = 0; k < 100; k++)
                {
                        assert(!p->isDead());
                        bool b = m.moveGarks();
                        if (!b || m.numGarksAt(1, 1) > 0 || p->isDead())
                        {
                                assert(!b && m.numGarksAt(1, 1) > 0 &&
                                                                p->isDead());
                                break;
                        }
                }
                assert(k < 100);
                        } break; case 30: {
                ostringstream oss;
                StreambufSwitcher sso2(cout, oss);
                Mesa m(2, 3);
                m.addPlayer(1, 2);
                m.addGark(1, 3);
                m.addGark(2, 2);
                m.display();
                string s = oss.str();
                assert(s.find(".@G") != string::npos);
                assert(s.find(".G.") != string::npos);
                        } break; case 31: {
                ostringstream oss;
                StreambufSwitcher sso2(cout, oss);
                Mesa m(2, 3);
                m.addPlayer(1, 2);
                for (int k = 1; k <= 8; k++)
                        m.addGark(1, 3);
                m.addGark(2, 2);
                m.display();
                string s = oss.str();
                assert(s.find(".@8") != string::npos);
                        } break; case 32: {
                ostringstream oss;
                StreambufSwitcher sbs(cout, oss);
                Mesa m(2, 3);
                m.addPlayer(1, 2);
                for (int k = 1; k <= 10; k++)
                        m.addGark(1, 3);
                m.addGark(2, 2);
                m.display();
                string s = oss.str();
                assert(s.find(".@9") != string::npos);
                        } break; case 33: {
                recordaddrs = true;
                int oldn = allocMap.size();
                {
                        Mesa m(10, 20);
                        int oldn2 = allocMap.size();
                        assert(oldn2 >= oldn);
                        m.addPlayer(4, 3);
                        m.addGark(5, 6);
                        m.addGark(5, 7);
                        m.addGark(5, 8);
                        assert(allocMap.size() == oldn2 + 4);
                }
                assert(allocMap.size() == oldn);
                recordaddrs = false;
                        } break; case 34: {
                Mesa m(1, 25);
                m.addPlayer(1, 2);
                recordaddrs = true;
                int oldn = allocMap.size();
                m.addGark(1, 5);
                assert(allocMap.size() == oldn + 1);
                m.attackGarkAt(1, 5, RIGHT);
                m.attackGarkAt(1, 6, RIGHT);
                assert(allocMap.size() == oldn);
                recordaddrs = false;
                        } break; case 35: {
                Mesa m(1, 25);
                m.addPlayer(1, 3);
                for (int k = 0; k < 20; k++)
                {
                        m.addGark(1, 2);
                        m.addGark(1, 4);
                }
                m.addGark(1, 25);
                for (int k = 0; k < 20; k++)
                {
                        m.addGark(1, 2);
                        m.addGark(1, 4);
                }
                assert(m.garkCount() == 81);
                for (int k = 0; k < 80; k++)
                {
                        m.attackGarkAt(1, 2, LEFT);
                        m.attackGarkAt(1, 4, RIGHT);
                }
                for (int k = 0; k < 80; k++)
                {
                        m.attackGarkAt(1, 1, LEFT);
                        m.attackGarkAt(1, 5, RIGHT);
                }
                assert(m.garkCount() == 1  &&  m.numGarksAt(1, 25) == 1);
                for (int c = 1; c <= 6; c++)
                        assert(m.numGarksAt(1, c) == 0);
                Player* p = m.player();
                assert(!p->isDead());
                for (int k = 0; k < 10; k++)
                {
                        m.moveGarks();
                        assert(!p->isDead());
                        for (int c = 1; c <= 6; c++)
                        {
                                m.attackGarkAt(1, c, RIGHT);
                                assert(m.numGarksAt(1, c) == 0);
                        }
                }
                        } break;
        }
}

int main()
{
    for (int n = 1; n<= 35; n++){
        testone(n);
        cout << "Passed!" << endl;
    }
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// YOU MAY MOVE TO ANOTHER FILE ALL THE CODE FROM HERE TO THE END OF FILE, BUT
// BE SURE TO MOVE *ALL* THE CODE; DON'T MODIFY OR REMOVE ANY #IFDEF, ETC.
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31/g32 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)


