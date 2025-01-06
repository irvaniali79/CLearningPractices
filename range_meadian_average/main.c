#include<stdio.h>
#include <math.h>
#include <stdlib.h>

struct athletTime
{
    int hour;
    int minute;
    int second;
};

void* setAthletTime(struct athletTime* source,struct athletTime* target){
    target->hour = source->hour;
    target->minute = source->minute;
    target->second = source->second;
}

void addAthletTime(struct athletTime* A,const struct athletTime* B){
    A->hour = A->hour+B->hour;
    A->minute = A->minute+B->minute;
    A->second = A->second+B->second;
}

void averageTime(struct athletTime* A, const int number){
    A->hour = A->hour/number;
    A->minute = A->minute/number;
    A->second = A->second/number;
}

void subtractAthletTime(struct athletTime* A,const struct athletTime* B){
    A->hour = A->hour-B->hour;
    A->minute = A->minute-B->minute;
    A->second = A->second-B->second;
}

struct statisticsAthlet
{
    struct athletTime range;
    struct athletTime average;
    struct athletTime median;
};

void printStatistics(const struct statisticsAthlet* sA){
    printf(
        "Range: %d|%d|%d Average: %d|%d|%d Median: %d|%d|%d",
        sA->range.hour,sA->range.minute,sA->range.second,
        sA->average.hour,sA->average.minute,sA->average.second,
        sA->median.hour,sA->median.minute,sA->median.second
    );
}

int athletTimeComparison(const void*  a, const void* b){
    const struct athletTime* timeA = (const struct athletTime*)a;
    const struct athletTime* timeB = (const struct athletTime*)b;

    if (timeA->hour != timeB->hour) {
        return timeA->hour - timeB->hour;
    }
    if (timeA->minute != timeB->minute) {
        return timeA->minute - timeB->minute;
    }
    return timeA->second - timeB->second;
}

void* sortArray(
        void* array,
        int sizeOfData,
        int n,
        int (* comparison)(const void*a, const void*b)
){
    qsort(array,n,sizeOfData,comparison);
}

void* calculateMedian(
        void* zeroData,
        void* sortedArray,
        int sizeOfData,
        int n,
        void (* add)(void* a,const void* b),
        void (* avg)(void* sum,const int number)
){
    if(n % 2){
        return &(sortedArray[n/2*sizeOfData]);
    }

    add(zeroData ,&(sortedArray[n/2*sizeOfData]));
    add(zeroData, &(sortedArray[(n/2-1)*sizeOfData]));
    avg(zeroData, 2);
    return zeroData;
}

void* calculateRange(
        void* zeroData,
        void* sortedArray,
        int dataSize,
        int n,
        void (* sub)(const void* a,const void*b)
){
    setAthletTime(&sortedArray[(n-1)*dataSize],zeroData);
    sub(zeroData,&sortedArray[0]);
    return zeroData;
}

int main(){
    struct athletTime times[3];
    struct athletTime sum = {0,0,0};
    int i = 0;
    for (i; i < 3; i++)
    {
        scanf("%d|%d|%d",&times[i].hour, &times[i].minute, &times[i].second);
        addAthletTime(&sum, &times[i]);
    }
    struct statisticsAthlet statistics;
    averageTime(&sum,i);
    statistics.average = sum;
    sortArray(times,sizeof(struct athletTime),i,athletTimeComparison);
    struct athletTime zeroData = {0,0,0};
    struct athletTime* tmpMedianVar = calculateMedian(&zeroData,times,sizeof(struct athletTime),i,addAthletTime,averageTime);
    setAthletTime(tmpMedianVar,&statistics.median);
    struct athletTime initData = {0,0,0};
    struct athletTime* tmpRangeVar = calculateRange(&initData,&times,sizeof(struct athletTime),i,subtractAthletTime);
    setAthletTime(tmpRangeVar,&statistics.range);
    printStatistics(&statistics);
    return 0;
}