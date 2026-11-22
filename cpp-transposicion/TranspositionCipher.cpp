#include "TranspositionCipher.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::sort y std::remove
#include <cmath>     // Para std::ceil
#include <map>
#include <limits>    // Para std::numeric_limits

// --- Lógica del Cifrado ---

// Función auxiliar para obtener el orden de las columnas basado en la clave
static std::vector<int> getKeyOrder(const std::string& key) {
    int keyLen = key.length();
    // Crea pares (caracter, índice_original)
    std::vector<std::pair<char, int>> sortedKey(keyLen);
    for (int i = 0; i < keyLen; ++i) {
        sortedKey[i] = {key[i], i};
    }

    // Ordena los pares alfabéticamente por caracter
    std::sort(sortedKey.begin(), sortedKey.end());

    // Extrae solo el orden de los índices originales
    std::vector<int> order(keyLen);
    for (int i = 0; i < keyLen; ++i) {
        order[i] = sortedKey[i].second;
    }
    return order; // Este es el orden en que se LEEN las columnas
}

std::string encryptColumnar(const std::string& text, const std::string& key) {
    if (key.empty()) return text;

    // 1. Limpiar el texto (opcional, pero recomendado)
    std::string cleanText = text;
    // Eliminar espacios (puedes ajustar esto)
    cleanText.erase(std::remove(cleanText.begin(), cleanText.end(), ' '), cleanText.end());

    int numCols = key.length();
    int numRows = (int)std::ceil((double)cleanText.length() / numCols);

    // 2. Rellenar texto para que complete la cuadrícula
    std::string paddedText = cleanText;
    int remainder = paddedText.length() % numCols;
    if (remainder != 0) {
        paddedText.append(numCols - remainder, 'X'); // Rellena con 'X'
    }
    numRows = paddedText.length() / numCols; // Recalcular filas (ahora es exacto)


    // 3. Crear y llenar la cuadrícula (fila por fila)
    std::vector<std::vector<char>> grid(numRows, std::vector<char>(numCols));
    int k = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j] = paddedText[k++];
        }
    }

    // 4. Obtener el orden de lectura de las columnas
    std::vector<int> colOrder = getKeyOrder(key);

    // 5. Leer la cuadrícula (columna por columna) según el orden de la clave
    std::string result = "";
    for (int col : colOrder) { // 'col' es el índice de la columna a leer
        for (int i = 0; i < numRows; ++i) {
            result += grid[i][col];
        }
    }

    return result;
}

std::string decryptColumnar(const std::string& cipher, const std::string& key) {
    if (key.empty()) return cipher;

    int numCols = key.length();
    if (cipher.length() % numCols != 0) {
        // Si no es divisible, la clave o el cifrado son incorrectos
        return "[Error: Longitud de cifrado no coincide con la clave]";
    }
    int numRows = cipher.length() / numCols;

    // 1. Obtener el orden de las columnas (igual que en el cifrado)
    std::vector<int> colOrder = getKeyOrder(key);

    // 2. Crear la cuadrícula
    std::vector<std::vector<char>> grid(numRows, std::vector<char>(numCols));

    // 3. Llenar la cuadrícula (columna por columna) según el orden
    int k = 0; // Índice para el texto cifrado
    for (int col : colOrder) { // 'col' es el índice de la columna a ESCRIBIR
        for (int i = 0; i < numRows; ++i) {
            grid[i][col] = cipher[k++];
        }
    }

    // 4. Leer la cuadrícula (fila por fila) para obtener el texto plano
    std::string result = "";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            result += grid[i][j];
        }
    }

    // Opcional: Eliminar el relleno 'X' del final
    // result.erase(result.find_last_not_of('X') + 1);

    return result;
}


// --- Interfaz Interactiva ---

void runTranspositionInteractive() {
    bool back = false;
    while (!back) {
        std::cout << "\n=== Cifrado por Transposicion Columnar ===\n";
        std::cout << "1. Cifrar\n";
        std::cout << "2. Descifrar\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Seleccione: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return; // Salir en caso de mala entrada
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

        if (choice == 0) {
            back = true;
            continue;
        }

        if (choice != 1 && choice != 2) {
             std::cout << "Opcion no valida.\n";
             continue;
        }

        std::string text, key;
        std::cout << "Ingrese el texto: ";
        std::getline(std::cin, text);
        std::cout << "Ingrese la clave (ej. 'CLAVE'): ";
        std::getline(std::cin, key);

        if (key.empty()) {
            std::cout << "Error: La clave no puede estar vacia.\n";
            continue;
        }
        // Limpiar la clave (quitar espacios, pasar a mayúsculas, etc.)
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);


        if (choice == 1) {
            std::string cipher = encryptColumnar(text, key);
            std::cout << "Texto Cifrado: " << cipher << "\n";
        } else if (choice == 2) {
            std::string plain = decryptColumnar(text, key);
            std::cout << "Texto Descifrado: " << plain << "\n";
        }
    }
}