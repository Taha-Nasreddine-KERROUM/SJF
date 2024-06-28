#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int bt;
    int wt;
    int tt;
    int rank;
} arr;

void read ( arr *x, int n ) {
    int i = 1;
    for ( arr *p = x + 1; p <= x + n; ++p ) {
        printf(" bt[%ld] = ", p - x);
        scanf("%d", &p -> bt);
        p -> rank = i++;
    }
}

void display ( arr *x, int n ) {
    printf("\n bt wt tt\n");
    for( arr *p = x + 1; p <= x + n; ++p )
        printf(" %02d %02d %02d\n", p -> bt, p -> wt, p -> tt);
}

void calc ( arr *x, int n ) {
    for( arr *p = x; p < x + n; ++p ) {
        (p + 1) -> wt = p -> bt + p -> wt;
        (p + 1) -> tt = p -> tt + (p + 1) -> bt;
    }
}

void avrg ( arr *x, int n, double *aw, double *at ) {
    for ( arr *p = x + 1; p <= x + n; ++p ) {
        *aw += p -> wt;
        *at += p -> tt;
    }
    *aw /= n;
    *at /= n;
}

void alloc ( arr **x, int n ){
    *x = ( arr* ) calloc ( n + 1, sizeof(arr) );
    if ( *x == NULL ) {
        printf(" memory contiguous allocation failed");
        exit(EXIT_FAILURE);
    }
}

void swap ( arr *a, arr *b ) {
    arr temp = *a;
    *a = *b;
    *b = temp;
}

void sort ( arr *x, int n ) {
    for ( arr *i = x + 1; i < x + n; ++i )
        for ( arr *j = x + 1; j < x + n; ++j )
            if ( j -> bt > (j + 1) -> bt )
                swap( j, j + 1);
}

void unsort ( arr *x, int n ) {
    for ( arr *i = x + 1; i < x + n; ++i )
        for ( arr *j = x + 1; j < x + n; ++j )
            if ( j -> rank > (j + 1) -> rank )
                swap( j, j + 1);
}

int main()
{
    int n;
    arr *t;
    double aw = 0, at = 0;
    
    printf(" Enter number of processes: ");
    scanf("%d", &n);
    
    alloc(&t, n);
    
    printf(" Enter burst time (execution time): \n");
    
    read(t, n);
    sort(t, n);
    calc(t, n);
    unsort(t, n);
    display(t, n);
    
    avrg(t, n, &aw, &at);
    printf("\n aw = %lf", aw);
    printf("\n at = %lf", at);
    
    free(t);
    t = NULL;
    return 0;
}
