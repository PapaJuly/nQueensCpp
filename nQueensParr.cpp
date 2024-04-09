//**************************************************************************
// N-Queens Solutions  ver3.3               takaken 2023/03/07
//**************************************************************************
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define  MAXSIZE   25
#define  MINSIZE    2
#define  i64  long long

//**********************************************
// Display the Board Image
//**********************************************
void Display(int n, int* board)
{
    int  y, bit, topb = 1 << (n - 1);

    printf("N= %d\n", n);
    for (y = 0; y < n; y++) {
        for (bit = topb; bit; bit >>= 1)
            printf("%s ", (board[y] & bit) ? "Q" : "-");
        printf("\n");
    }
    printf("\n");
}
//**********************************************
// Check Unique Solutions
//**********************************************
void Check(int* board, int size, int topb, int posA, int bitB, int posC, i64* cnt8, i64* cnt4, i64* cnt2)
{
    int  pos1, pos2, bit1, bit2;

    // 90-degree rotation
    if (board[posA] == 1) {
        for (pos1 = 1, bit2 = 2; pos1 < size; pos1++, bit2 <<= 1) {
            for (pos2 = size - 1, bit1 = 1; board[pos1] != bit1 && board[pos2] != bit2; pos2--, bit1 <<= 1);
            if (board[pos1] != bit1) return;
            if (board[pos2] != bit2) break;
        }
        if (pos1 == size) {
            (*cnt2)++;
            //Display(size, board);
            return;
        }
    }

    // 180-degree rotation
    if (board[size - 1] == bitB) {
        for (pos1 = 1, pos2 = size - 2; pos1 < size; pos1++, pos2--) {
            for (bit2 = topb, bit1 = 1; board[pos1] != bit1 && board[pos2] != bit2; bit2 >>= 1, bit1 <<= 1);
            if (board[pos1] != bit1) return;
            if (board[pos2] != bit2) break;
        }
        if (pos1 == size) {
            (*cnt4)++;
            //Display(size, board);
            return;
        }
    }

    // 270-degree rotation
    if (board[posC] == topb) {
        for (pos1 = 1, bit2 = topb >> 1; pos1 < size; pos1++, bit2 >>= 1) {
            for (pos2 = 0, bit1 = 1; board[pos1] != bit1 && board[pos2] != bit2; pos2++, bit1 <<= 1);
            if (board[pos1] != bit1) return;
            if (board[pos2] != bit2) break;
        }
    }

    (*cnt8)++;
    //Display(size, board);
}
//**********************************************
// First queen is inside
//**********************************************
void Inside(int n, int x0, int x1, i64* unq, i64* ttl)
{
    int  size, last, y, i;
    int  bits, bit, mask, left, rigt;
    int  posA, bitB, posC, topb, side, gate;
    int  board[MAXSIZE];
    int  s_mask[MAXSIZE];
    int  s_left[MAXSIZE];
    int  s_rigt[MAXSIZE];
    int  s_bits[MAXSIZE];
    i64  cnt8, cnt4, cnt2;

    // first check
    if (x1 >= (x0 - 1) && x1 <= (x0 + 1)) return;
    if (x0 > 1 && (x1 == 0 || x1 == (n - 1))) return;

    // Initialize
    size = n;
    last = n - 1;
    mask = (1 << n) - 1;
    cnt8 = cnt4 = cnt2 = 0;

    // ControlValue
    topb = 1 << last;
    side = topb | 1;
    gate = (mask >> x0) & (mask << x0);
    posA = last - x0;
    bitB = topb >> x0;
    posC = x0;

    // x0: 000001110 (select)
    // x1: 111111111 (select)
    board[0] = 1 << x0;
    board[1] = 1 << x1;
    mask = mask ^ (board[0] | board[1]);
    left = board[0] << 2 | board[1] << 1;
    rigt = board[0] >> 2 | board[1] >> 1;
    y = i = 2;

    // y(=2) -> posA (N = 4)
    if (posA == 2) {
        bits = mask & ~(left | rigt);
        goto NEXT3;
    }

    //-------------------------
    // y(=2) -> posC
    //-------------------------
    if (posC == 1) goto NEXT2;
    mask = mask ^ side;
NEXT1:
    if (i == posC) {
        mask |= side;
        goto NEXT2;
    }
    bits = mask & ~(left | rigt);
    if (bits) {
        s_mask[i] = mask;
        s_left[i] = left;
        s_rigt[i] = rigt;
    PROC1:
        bits ^= bit = -bits & bits;
        board[i] = bit;
        s_bits[i++] = bits;
        mask = mask ^ bit;
        left = (left | bit) << 1;
        rigt = (rigt | bit) >> 1;
        goto NEXT1;
    BACK1:
        bits = s_bits[--i];
        if (bits) {
            mask = s_mask[i];
            left = s_left[i];
            rigt = s_rigt[i];
            goto PROC1;
        }
    }
    if (i == y) goto FINISH;
    goto BACK1;

    //-------------------------
    // posC -> posA
    //-------------------------
NEXT2:
    bits = mask & ~(left | rigt);
    if (bits) {
        s_mask[i] = mask;
        s_left[i] = left;
        s_rigt[i] = rigt;
    PROC2:
        bits ^= bit = -bits & bits;
        board[i] = bit;
        s_bits[i++] = bits;
        mask = mask ^ bit;
        left = (left | bit) << 1;
        rigt = (rigt | bit) >> 1;
        if (i == posA) {
            if (mask & topb) goto BACK2;
            if (mask & 1) {
                if ((left | rigt) & 1) goto BACK2;
                bits = 1;
            } else {
                bits = mask & ~(left | rigt);
                if (!bits) goto BACK2;
                // check of lastline bits and gate
                if (!(gate & mask & ~(left << (last - i) | rigt >> (last - i)))) goto BACK2;
            }
            goto NEXT3;
        } else {
            goto NEXT2;
        }
    BACK2:
        bits = s_bits[--i];
        if (bits) {
            mask = s_mask[i];
            left = s_left[i];
            rigt = s_rigt[i];
            goto PROC2;
        }
    }
    if (i == y) goto FINISH;
    if (i > posC) goto BACK2;
    goto BACK1;

    //-------------------------
    // posA -> last
    //-------------------------
NEXT3:
    if (i == last) {
        board[i] = bits;
        Check(board, size, topb, posA, bitB, posC, &cnt8, &cnt4, &cnt2);
        goto BACK3;
    }
    s_mask[i] = mask;
    s_left[i] = left;
    s_rigt[i] = rigt;
PROC3:
    bits ^= bit = -bits & bits;
    board[i] = bit;
    s_bits[i++] = bits;
    mask = mask ^ bit;
    left = (left | bit) << 1;
    rigt = (rigt | bit) >> 1;
    bits = mask & ~(left | rigt);
    if (!bits) goto BACK3;
    // check of lastline bits and gate
    if (!(gate & mask & ~(left << (last - i) | rigt >> (last - i)))) goto BACK3;
    goto NEXT3;
BACK3:
    bits = s_bits[--i];
    if (bits) {
        mask = s_mask[i];
        left = s_left[i];
        rigt = s_rigt[i];
        goto PROC3;
    }
    if (i == y) goto FINISH;
    if (i > posA) goto BACK3;
    goto BACK2;

FINISH:
    *unq += cnt8 + cnt4 + cnt2;
    *ttl += cnt8 * 8 + cnt4 * 4 + cnt2 * 2;
}
//**********************************************
// First queen is in the corner
//**********************************************
void Corner(int n, int x1, i64* unq, i64* ttl)
{
    int  size, last, y, i;
    int  bits, bit, mask, left, rigt;
    int  posA;
    int  board[MAXSIZE];
    int  s_mask[MAXSIZE];
    int  s_left[MAXSIZE];
    int  s_rigt[MAXSIZE];
    int  s_bits[MAXSIZE];
    i64  cnt8;

    // Initialize
    size = n;
    last = n - 1;
    mask = (1 << n) - 1;
    cnt8 = 0;

    // ControlValue
    posA = x1;

    // x0: 000000001 (static)
    // x1: 011111100 (select)
    board[0] = 1;
    board[1] = bit = 1 << x1;
    mask = mask ^ (1 | bit);
    left = 1 << 2 | bit << 1;
    rigt = 1 >> 2 | bit >> 1;
    y = i = 2;

    //-------------------------
    // y(=2) -> posA
    //-------------------------
    mask = mask ^ 2;
NEXT1:
    if (i == posA) {
        mask |= 2;
        goto NEXT2;
    }
    bits = mask & ~(left | rigt);
    if (bits) {
        s_mask[i] = mask;
        s_left[i] = left;
        s_rigt[i] = rigt;
    PROC1:
        bits ^= bit = -bits & bits;
        board[i] = bit;
        s_bits[i++] = bits;
        mask = mask ^ bit;
        left = (left | bit) << 1;
        rigt = (rigt | bit) >> 1;
        goto NEXT1;
    BACK1:
        bits = s_bits[--i];
        if (bits) {
            mask = s_mask[i];
            left = s_left[i];
            rigt = s_rigt[i];
            goto PROC1;
        }
    }
    if (i == y) goto FINISH;
    goto BACK1;

    //-------------------------
    // posA -> last
    //-------------------------
NEXT2:
    bits = mask & ~(left | rigt);
    if (bits) {
        if (i == last) {
            board[i] = bits;
            cnt8++;
            //Display(size, board);
            goto BACK2;
        }
        s_mask[i] = mask;
        s_left[i] = left;
        s_rigt[i] = rigt;
    PROC2:
        bits ^= bit = -bits & bits;
        board[i] = bit;
        s_bits[i++] = bits;
        mask = mask ^ bit;
        left = (left | bit) << 1;
        rigt = (rigt | bit) >> 1;
        goto NEXT2;
    BACK2:
        bits = s_bits[--i];
        if (bits) {
            mask = s_mask[i];
            left = s_left[i];
            rigt = s_rigt[i];
            goto PROC2;
        }
    }
    if (i == y) goto FINISH;
    if (i > posA) goto BACK2;
    goto BACK1;

FINISH:
    *unq += cnt8;
    *ttl += cnt8 * 8;
}
//**********************************************
// Search of N-Queens
//**********************************************
void NQueens(int n, i64* unique, i64* total)
{
    int  i, x0, x1;
    i64  unq[MAXSIZE], ttl[MAXSIZE];

    // Initialize (omp memory)
    for (i = 0; i < n; i++)
        unq[i] = ttl[i] = 0;

    // First queen is in the corner
    // y=0: 000000001 (static)
    // y=1: 011111100 (select)
    #pragma omp parallel for
    for (x1 = 2; x1 < (n-1); x1++) {
        Corner(n, x1, &unq[x1], &ttl[x1]);
    }

    // First queen is inside
    // y=0: 000001110 (select)
    // y=1: 111111111 (select)
    for (x0 = 1; x0 < n / 2; x0++) {
        #pragma omp parallel for
        for (x1 = 0; x1 < n; x1++) {
            Inside(n, x0, x1, &unq[x1], &ttl[x1]);
        }
    }

    // Totalling (omp memory -> shared memory)
    for (i = 0; i < n; i++) {
        *unique += unq[i];
        *total += ttl[i];
    }
}
//**********************************************
// Format of Used Time
//**********************************************
void TimeFormat(clock_t utime, char* form)
{
    int  dd, hh, mm;
    double ftime, ss;

    ftime = (double)utime / CLOCKS_PER_SEC;

    mm = (int)ftime / 60;
    ss = ftime - (double)(mm * 60);
    dd = mm / (24 * 60);
    mm = mm % (24 * 60);
    hh = mm / 60;
    mm = mm % 60;

    if (dd) snprintf(form, 20, "%4d %02d:%02d:%05.2f", dd, hh, mm, ss);
    else if (hh) snprintf(form, 20, "     %2d:%02d:%05.2f", hh, mm, ss);
    else if (mm) snprintf(form, 20, "        %2d:%05.2f", mm, ss);
    else snprintf(form, 20, "           %5.2f", ss);
}
//**********************************************
// N-Queens Solutions MAIN
//**********************************************
int main(void)
{
    int  n;
    i64  unique, total;
    clock_t starttime;
    char form[20];

    printf("<------  N-Queens Solutions  -----> <---- time ---->\n");
    printf(" N:           Total          Unique days hh:mm:ss.--\n");
    for (n = MINSIZE; n <= MAXSIZE; n++) {
        starttime = clock();
        unique = total = 0;
        NQueens(n, &unique, &total);
        TimeFormat(clock() - starttime, form);
        printf("%2d:%11lld%11lld %s\n", n, total, unique, form);
    }

    return 0;
}