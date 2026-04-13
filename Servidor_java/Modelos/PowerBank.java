package Servidor_java.Modelos;

public class PowerBank extends Produto {
    
    private String marca;
    private String modelo;
    private int tempo_de_bateria;

    public PowerBank(int id,String nome, String descricao,double preco,int estoque,String marca,String modelo,int tempo_de_bateria){

        super(id,nome,descricao,preco,estoque);

        this.marca = marca;
        this.modelo = modelo;
        this.tempo_de_bateria = tempo_de_bateria;

    }

    public String getMarca(){return marca;}
    public String getModelo(){return modelo;}
    public int getTempo_de_bateria(){return tempo_de_bateria;} 

    public void setMarca(String marca){this.marca = marca;}
    public void setModelo(String modelo){this.modelo = modelo;}
    public void setTempo_de_bateria(int tempo_de_bateria){this.tempo_de_bateria = tempo_de_bateria;}

    public String toString() {
        return "PowerBank [id=" + getId() + ", nome=" + getNome() + ", preco=" + getPreco() + ", estoque=" + getEstoque() + "Marca="+ marca + "modelo="+ modelo + "Duracao" + tempo_de_bateria +"MA/h ]";
    }    

}
