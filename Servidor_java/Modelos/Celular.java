package Servidor_java.Modelos;
public class Celular extends Produto{

    private String marca;
    private String modelo;
    

    public Celular(int id,String nome,String descricao,double preco,int estoque,String marca,String modelo){

        super(id,nome,descricao,preco,estoque);

        this.marca = marca;
        this.modelo = modelo;
    }

    public String getMarca(){return marca;}
    public String getModelo(){return modelo;}

    public void setMarca(String marca){this.marca = marca;}
    public void setModelo(String modelo){this.modelo = modelo;}

    public String toString() {
        return "Celular [id=" + getId() + ", nome=" + getNome() + ", preco=" + getPreco() + ", estoque=" + getEstoque() + "Marca="+ marca + "modelo="+ modelo +"]";
    }

}