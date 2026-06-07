package Servidor_java.Modelos;

public class PowerBank extends Produto {
    
    private String marca;
    private String modelo;
    private int capacidade;

    public PowerBank(){
        super();
    }

    public PowerBank(int id,String nome, String descricao,double preco,int estoque,String marca,String modelo,int capacidade){

        super(id,nome,descricao,preco,estoque);

        this.marca = marca;
        this.modelo = modelo;
        this.capacidade = capacidade;

    }

    public String getMarca(){return marca;}
    public String getModelo(){return modelo;}
    public int getcapacidade(){return capacidade;} 

    public void setMarca(String marca){this.marca = marca;}
    public void setModelo(String modelo){this.modelo = modelo;}
    public void setcapacidade(int capacidade){this.capacidade = capacidade;}

    public String toString() {
        return "PowerBank [id=" + getId() + ", nome=" + getNome() + ", preco=" + getPreco() + ", estoque=" + getEstoque() + "Marca="+ marca + "modelo="+ modelo + "Duracao" + capacidade +"MA/h ]";
    }    

}
