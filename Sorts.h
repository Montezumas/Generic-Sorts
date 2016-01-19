#ifndef _SORTS_H_
#define _SORTS_H_

template <class T> class Sorts{
	public:
		static void insertion_sort(T *array, int length);
		static void insertion_sort(T *array, int left, int right);
		static void heapsort(T *array, int size);
		static void mergesort(T *array, int size);
		static void quicksort(T *array, int size);
	private:
		static void heapify(T *array, int size);
		static void percolateDown(T *array, int size, int index);
		static T deleteMax(T *array, int size);
		static void mergesort(T *array, int left, int right, T *tmp);
		static void merge(T *array, int left, int middle, int right, T *tmp);
		static void quicksort(T *array, int left, int right);
		static int partition(T *array, int left, int right, int pivot);
		static void swap(T *array, int a, int b);
};

template <class T> void Sorts<T>::insertion_sort(T *array, int length){
	for (int i=1;i<length-1;i++){
		T tmp = array[i];
		int j = i;
		while ((j>=1) && (array[j-1]>tmp)){
			array[j] = array[j-1];
			j--;
		}
		array[j]= tmp;
 	}
}

template <class T> void Sorts<T>::insertion_sort(T *array, int left, int right){
	for (int i=left+1;i<right+1;i++){
		T tmp = array[i];
		int j = i;
		while ((j>=left+1) && (array[j-1]>tmp)){
			array[j] = array[j-1];
			j--;
		}
		array[j]= tmp;
 	}
}

template <class T> void Sorts<T>::heapsort(T *array, int size){
	heapify(array,size);

	int tempSize = size;
	for(int i = 0; i < size; i++){
		array[size-(i+1)] = deleteMax(array,tempSize);
		tempSize--;
	}
}

template <class T> void Sorts<T>::heapify(T *array, int size){
	for(int i = ((size/2)); i>=0; i--){
		percolateDown(array,size,i);
	}
}

template <class T> void Sorts<T>::percolateDown(T *array, int size, int index){
	T temp = array[index];
	int hole = index;
	int child = (2*hole)+1;

	if((child <= size) && ((child+1) < size) && (array[child+1] > array[child])){
		child++;
	}

	while((hole <= size) && (child <= size) && (array[child] > temp)){
		array[hole] = array[child];
		hole = child;

		child = (2*hole)+1;
		if((child <= size) && ((child+1) < size) && (array[child+1] > array[child])){
			child++;
		}
	}

	array[hole] = temp;
}

template <class T> T Sorts<T>::deleteMax(T *array, int size){
	T temp = array[0];
	array[0] = array[size-1];
	size--;
	percolateDown(array,size,0);
	return temp;
}

template <class T> void Sorts<T>::mergesort(T* array, int size){
	T *tmp = new T[size];
	mergesort(array,0,size-1,tmp);
	delete []tmp;
}

template <class T> void Sorts<T>::mergesort(T *array, int left, int right, T *tmp){
	if(left < right){
		int middle = ((left+right)/2);

		if((middle-left) <= 50){
			insertion_sort(array, left, middle);
		}	else {
			mergesort(array,left,middle,tmp);
		}

		if((right-(middle+1)) <= 50){
			insertion_sort(array,middle+1,right);
		}	else{
			mergesort(array,middle+1,right,tmp);
		}

		merge(array,left,middle,right,tmp);
	}

}

template <class T> void Sorts<T>::merge(T *array, int left, int middle, int right, T *tmp){
	int i = left;
	int j = middle+1;
	int k = left;

	while((i<=middle) && (j<=right)){
		if(array[i] < array[j]){
			tmp[k] = array[i];
			i++;
		}	else{
			tmp[k] = array[j];
			j++;
		}
		k++;
	}

	for(;i<=middle;i++,k++){
		tmp[k] = array[i];
	}
	for(;j<=right;j++,k++){
		tmp[k] = array[j];
	}
	for(i=left;i<=right;i++){
		array[i] = tmp[i];
	}
}

template <class T> void Sorts<T>::quicksort(T *array, int size){
	quicksort(array, 0, size-1);
}

template <class T> void Sorts<T>::quicksort(T *array, int left, int right){
	if(left<right){
		int middle = (right+left)/2;
		
		int pivot = 0;
		if((array[left] < array[right] && array[left] > array[middle]) || (array[left] > array[right] && array[left] < array[middle])){
			pivot = left;
		}	else if((array[right] < array[middle] && array[right] > array[left]) || (array[right] > array[middle] && array[right] < array[left])){
			pivot = right;
		}	else{
			pivot = middle;
		}

		pivot = partition(array, left, right, pivot);

		quicksort(array,left,pivot-1);
		quicksort(array,pivot+1,right);
	}
}

template <class T> int Sorts<T>::partition(T *array, int left, int right, int pivot){
	swap(array, pivot, right);
	T data = array[right];
	int i = left - 1;

	for(int j=left; j < right; j++){
		if(array[j]<=data){
			i++;
			swap(array,i,j);
		}
	}

	swap(array, i+1, right);
	return i+1;
}

template <class T> void Sorts<T>::swap(T *array, int a, int b){
	T temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

#endif
