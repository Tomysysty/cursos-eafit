#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include <string>

/**
 * @brief Ejecuta el submenú interactivo para el Cifrado por Transposición Columnar.
 */
void runTranspositionInteractive();

/**
 * @brief Cifra un texto usando Transposición Columnar.
 * @param text El texto plano a cifrar.
 * @param key La palabra clave.
 * @return El texto cifrado.
 */
std::string encryptColumnar(const std::string& text, const std::string& key);

/**
 * @brief Descifra un texto usando Transposición Columnar.
 * @param cipher El texto cifrado.
 * @param key La palabra clave.
 * @return El texto plano (puede tener caracteres de relleno al final).
 */
std::string decryptColumnar(const std::string& cipher, const std::string& key);

#endif // TRANSPOSITIONCIPHER_H