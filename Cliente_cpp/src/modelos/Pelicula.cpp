#include "modelos/Pelicula.h"
#include <string>
#include <iostream>


Pelicula::Pelicula(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque, const std::string& tipo)
                    : Produto(id, nome, descricao, preco, quantidade_estoque), tipo(tipo) {
}


TipoProduto Pelicula::getTipo() const {
    return TipoProduto::PELICULA;
}

void Pelicula::mostrar() const {
    Produto::mostrar();
    std::cout << "Tipo: " << tipo << std::endl;
}

std::string Pelicula::getTipoPelicula() const {
    return tipo;
}

void Pelicula::setTipoPelicula(const std::string& tipo) {
    this->tipo = tipo;
}




