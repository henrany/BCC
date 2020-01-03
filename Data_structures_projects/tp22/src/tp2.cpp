#include"tp2.h"

Rick::Rick(){

}
 
//time complexity of O(n)
//adding values into the vector
void Rick::add_visit(visit vec[], int n){
    for(int i=0;i<n;i++){
        std::cin>>vec[i].time>>vec[i].name;
    }
}

//time complexity of O(n log n)
//merge two subarrays
void Rick::merge(visit vec[], int beg, int mid, int end){
    int left = mid - beg + 1;
    int right = end - mid;

    visit *left_vec = new visit[left];
    visit *right_vec = new visit[right];

    for(int i=0;i<left;i++){
        left_vec[i] = vec[beg + i]; 
    }

    for(int j=0;j<right;j++){
        right_vec[j] = vec[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = beg;
    while(i<left && j<right){
        if(left_vec[i].time <= right_vec[j].time){
            vec[k] = left_vec[i];
            i++;
        }
        else{
            vec[k] = right_vec[j];
            j++;
        }
        k++;
    }

    while(i<left){
        vec[k] = left_vec[i];
        i++;
        k++;
    }

    while(j<right){
        vec[k] = right_vec[j];
        j++;
        k++;
    }

}
 
 //time complexity of O(n log n)
 //sorting the the time
void Rick::merge_sort(visit vec[], int beg, int end){
    if(beg<end){
        int mid = (beg + end)/2;
        merge_sort(vec, beg, mid);
        merge_sort(vec, mid+1, end);
        merge(vec, beg, mid, end);
    }
}


//time complexity of O(n*k)
//sorting the letters
void Rick::radix_sort(visit vec[], int n,int length){
    visit *temp = (visit *)calloc(n,sizeof(visit));

    for(int d =length-1;d>=0;d--){
        int *count = (int *)calloc(257,sizeof(int));
        for(int i=0;i<n;i++)
            count[vec[i].name.at(d) + 1]++;
        for(int r=0;r<256;r++)
            count[r+1] += count[r];
        for(int i=0;i<n;i++)
            temp[count[vec[i].name.at(d)]++] = vec[i];
        for(int i=0;i<n;i++)
            vec[i] = temp[i];
        free(count);
    }
    free(temp);
}

//time complexity of O(n^2)
//sorting the count
void Rick::insertion_sort(visit vec[], int n){
    int i, j;
    visit key;
    for (i = 1; i < n; i++) 
    {  
        j=i;
        while(j>0 && vec[j].count < vec[j-1].count){
            key = vec[j];
            vec[j] = vec[j-1];
            vec[j-1] = key;
            j--;
        } 
    }  
}


//time complexity of O(n)
//adding values to months
void Rick::sort_visit(visit vec[], int n, int tot_time){
    merge_sort(vec,0,n-1);
    int count=0;
    int sum=0;
    for(int i = 0; i<n; i++){
        sum += vec[i].time; 
        vec[i].count += count;

        if(i < n-1 && (sum + vec[i+1].time) > tot_time){
            sum = 0;
            count++;
        }
    }
}


//time complexity of O(n)
//print the function
void Rick::print(visit vec[], int n){
    for(int i=0;i<n;i++){
        std::cout<<vec[i].count<<" "<<vec[i].name << " "<< vec[i].time<<" \n";
    }
}

Rick::~Rick(){

}