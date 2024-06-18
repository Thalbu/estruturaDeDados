// funcoesDeOrdenacao.cpp
#include <iostream>
#include <chrono>
#include "funcoesDeOrdenacao.h"

// Método da bolha
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Método da inserção
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Método da seleção
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Arrays temporários para armazenar os elementos das duas metades
    int L[n1], R[n2];

    // Copiando dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Mesclando os arrays temporários de volta para arr[l..r]
    int i = 0; // Índice inicial do primeiro subarray
    int j = 0; // Índice inicial do segundo subarray
    int k = l; // Índice inicial do array mesclado resultante
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiando os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}




// Quick Sort
// -Função auxiliar para trocar dois elementos no array
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// -Função que retorna o índice correto do pivô no array ordenado
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivô é o último elemento
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++; // Incrementa o índice do menor elemento
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// -Função principal que implementa o algoritmo Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Particiona o array e obtém o índice do pivô
        int pi = partition(arr, low, high);

        // Ordena separadamente os elementos antes e depois do pivô
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Shell Sort
void shellSort(int arr[], int n) {
    // Começa com um grande intervalo e reduz gradualmente
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Fazemos um passe de inserção para o intervalo gap
        for (int i = gap; i < n; i++) {
            // Pega o elemento em arr[i] que será inserido na sequência ordenada
            int temp = arr[i];

            // Move os elementos arr[0..i-gap], arr[0+gap..i-gap+gap], arr[0+2*gap..i-gap+2*gap]...
            // até encontrarmos a posição correta para arr[i]
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Coloca o elemento em sua posição correta
            arr[j] = temp;
        }
    }
}

// Counting Sort
// -Função para encontrar o valor máximo no array
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// -Função principal do Counting Sort
void countingSort(int arr[], int n) {
    if (n <= 1) {
        return;
    }

    // Encontra o valor máximo no array para determinar o tamanho necessário do array de contagem
    int max = findMax(arr, n);

    // Cria um array de contagem com base no valor máximo encontrado
    int count[max + 1] = {0};

    // Conta a frequência de cada elemento
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }

    // Modifica o array de contagem para que cada elemento indique sua posição no array ordenado
    for (int i = 1; i <= max; ++i) {
        count[i] += count[i - 1];
    }

    // Cria um array de saída que contém os elementos ordenados
    int output[n];
    for (int i = n - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copia o array ordenado de volta para o array original
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// Bucket Sort
// -Função auxiliar para inserir elementos em um balde
// -Definição de uma estrutura de lista encadeada simples para os baldes
struct Node {
    int data;
    Node* next;
};

// -Função para inserir um elemento no final da lista encadeada (bucket)
void insertInBucket(Node* &bucket, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (!bucket) {
        bucket = newNode;
    } else {
        Node* temp = bucket;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// -Função para ordenar a lista encadeada (bucket) usando Insertion Sort
void sortBucket(Node* &bucket) {
    if (!bucket || !bucket->next) {
        return;
    }

    Node* sorted = nullptr;
    Node* current = bucket;
    while (current) {
        Node* next = current->next;

        // Inserir current na lista ordenada sorted
        if (!sorted || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next && temp->next->data <= current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    bucket = sorted;
}

// -Função principal que implementa o Bucket Sort
void bucketSort(int arr[], int n) {
    if (n <= 1) {
        return;
    }

    // Determina o número de baldes (fixo em 10 para este exemplo)
    const int num_buckets = 10;
    Node* buckets[num_buckets] = {nullptr};

    // Distribui os elementos pelos baldes
    for (int i = 0; i < n; ++i) {
        int bucket_index = arr[i] / 10; // Intervalo de 0 a 9, dependendo do valor do elemento
        insertInBucket(buckets[bucket_index], arr[i]);
    }

    // Ordena cada balde e coloca os elementos ordenados de volta no array original
    int index = 0;
    for (int i = 0; i < num_buckets; ++i) {
        sortBucket(buckets[i]);
        Node* temp = buckets[i];
        while (temp) {
            arr[index++] = temp->data;
            temp = temp->next;
        }

        // Libera a memória dos nós da lista encadeada (bucket)
        Node* current = buckets[i];
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

// Radix Sort
// Função para realizar o Counting Sort baseado no dígito específico (exp)
void countingSort(int arr[], int n, int exp) {
    int output[n]; // Array de saída
    int count[10] = {0}; // Array de contagem para armazenar a contagem de dígitos

    // Conta a contagem de ocorrências de cada dígito em count[]
    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }

    // Muda count[i] para que count[i] agora contenha a posição real deste dígito no output[]
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Cria o array de saída usando o array de contagem
    for (int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copia o array de saída para arr[], para que arr[] contenha números ordenados de acordo com o dígito atual
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// Função principal que implementa o Radix Sort
void radixSort(int arr[], int n) {
    // Encontra o número máximo para saber o número de dígitos
    int m = findMax(arr, n);

    // Aplica o counting sort para cada dígito. exp é 10^i onde i é o dígito atual
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

// Mede o tempo das funções
void measureExecutionTime(int arr[], int n, void (*sortFunc)(int[], int)) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
}

