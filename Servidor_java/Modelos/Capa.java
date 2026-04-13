package Servidor_java.Modelos;

public class Capa extends Produto{
    private String cor;
    private String modelo;
    private String material;
    

    public Capa(int id,String nome,String descricao,double preco,int estoque,String cor,String modelo,String material){

        super(id,nome,descricao,preco,estoque);

        this.cor = cor;
        this.modelo = modelo;
        this.material = material;
    }

    public String getcor(){return cor;}
    public String getModelo(){return modelo;}
    public String getMaterial(){return material;}

    public void setcor(String cor){this.cor = cor;}
    public void setModelo(String modelo){this.modelo = modelo;}
    public void setMaterial(String material){this.material = material;}

    public String toString() {
        return "Capinha [id=" + getId() + ", nome=" + getNome() + ", preco=" + getPreco() + ", estoque=" + getEstoque() + "cor="+ cor + "modelo="+ modelo + "material="+ material +"]";
    }

}
