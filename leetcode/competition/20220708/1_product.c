#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

struct line_cur {
    bool busy;
    int s_date;
    int productID;
};

typedef struct {
    int n_line;
    int n_product;
    int *periods;
    struct line_cur *cur_lines;
    int *product;
} ProductionLineMgmtSys;

ProductionLineMgmtSys *ProductionLineMgmtSysCreate(int num, int *periods, int periodsSize)
{
    int i;
    ProductionLineMgmtSys *sys = (ProductionLineMgmtSys *)malloc(sizeof(ProductionLineMgmtSys));

    sys->n_line = num;
    sys->n_product = periodsSize;
    sys->periods = (int *)malloc(sizeof(int) * periodsSize);
    sys->product = (int *)malloc(sizeof(int) * periodsSize);
    sys->cur_lines = (struct line_cur *)malloc(sizeof(struct line_cur) * num);

    for (i = 0; i < periodsSize; i++) {
        sys->periods[i] = periods[i];
        sys->product[i] = 0;
    }

    for (i = 0; i < num; i++) {
        sys->cur_lines[i].busy = false;
    }

    return sys;
}

int calc_product(ProductionLineMgmtSys *sys, int productId, int s_date, int e_date)
{
    int period = sys->periods[productId];
    int n = (e_date - s_date) / period;
    sys->product[productId] += n;

    // printf("s %d e %d productId %d period %d\n", s_date, e_date, productId, period);
    // printf("t: %d produce %d: %d\n", e_date, productId, n);

    return (e_date - s_date) % period;
}

int ProductionLineMgmtSysProduce(ProductionLineMgmtSys *sys, int date, int assemblyId, int productId)
{
    assert(assemblyId < sys->n_line);

    struct line_cur *line_status = sys->cur_lines + assemblyId;
    if (!line_status->busy) {
        line_status->busy = true;
        line_status->s_date = date;
        line_status->productID = productId;

        return 1;
    }

    if (line_status->productID == productId) {
        return 0;
    }

    int s_date = line_status->s_date;
    int e_date = date;

    (void)calc_product(sys, line_status->productID, s_date, e_date);
    line_status->s_date = date;
    line_status->productID = productId;

    return -1;
}

int ProductionLineMgmtSysGetProductCount(ProductionLineMgmtSys *sys, int date, int productId)
{
    int i;
    int remain;

    for (i = 0; i < sys->n_line; i++) {
        if (sys->cur_lines[i].productID != productId)
            continue;

        remain = calc_product(sys, productId, sys->cur_lines[i].s_date, date);
        sys->cur_lines[i].s_date = date - remain;
    }

    return sys->product[productId];
}

void ProductionLineMgmtSysFree(ProductionLineMgmtSys *sys)
{
    free(sys->periods);
    free(sys->product);
    free(sys->cur_lines);
    free(sys);
}

int main()
{
    return 0;
}