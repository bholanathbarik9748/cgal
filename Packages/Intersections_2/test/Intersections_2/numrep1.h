#if TESTR == 1

#include <CGAL/Cartesian.h>

inline double to_nt(int d)
{
    return double(d);
}
#endif

#if TESTR == 2

#include <CGAL/Homogeneous.h>

inline double to_nt(int d)
{
    return d;
}
#endif


#if TESTR == 3

#include <CGAL/test_types.h>
#include <CGAL/Cartesian.h>

inline CGAL_TestfieldC to_nt(int d)
{
    unsigned char dummy1 = 'a';
    signed char dummy2 = 'a';
    return CGAL_TestfieldC(dummy1, dummy2, (double)d);
}

#endif


#if TESTR == 4

#include <CGAL/test_types.h>
#include <CGAL/Homogeneous.h>

inline CGAL_TestrepH to_nt(int d)
{
    unsigned char dummy1 = 'a';
    signed char dummy2 = 'a';
    return CGAL_TestrepH(dummy1, dummy2, d);
}
#endif

#if TESTR == 5

#include <CGAL/Homogeneous.h>
#include <CGAL/Integer.h>

#include <LEDA/REDEFINE_NAMES.h>
inline integer to_nt(int d)
{
    return integer(d);
}
#include <LEDA/UNDEFINE_NAMES.h>
#endif

struct randomint {
    randomint() ;
    int	get() const { return sequence[cur]; }
    int next() { cur = (cur+1)%11; return get();}
private:
    int sequence[11];
    int cur;
};

inline randomint::randomint()
{
    cur = 0;
    sequence[0] = 19;
    sequence[1] = 5;
    sequence[2] = 17;
    sequence[3] = 13;
    sequence[4] = 29;
    sequence[5] = 2;
    sequence[6] = 23;
    sequence[7] = 31;
    sequence[8] = 3;
    sequence[9] = 37;
    sequence[10] = 11;
}

