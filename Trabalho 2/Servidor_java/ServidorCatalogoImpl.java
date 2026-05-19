package Servidor_java;

import CatalogoApp.*; // Pacote gerado pelo idlj
import org.omg.CORBA.ORB;
import org.json.JSONObject;
import Servidor_java.Servicos.CatalogoProdutos;

public class ServidorCatalogoImpl extends ServicoCatalogoPOA {
    
    private Despachante despachante;

    public ServidorCatalogoImpl(CatalogoProdutos catalogo) {
        // Inicializa o despachante passando a referência do banco de dados na memória
        this.despachante = new Despachante(catalogo);
    }

    @Override
    public byte[] doOperation(String objectRef, int methodId, byte[] arguments) {
        try {
            // 1. RECEBER A REQUISIÇÃO (getRequest implicito via bytes do CORBA)
            String jsonFormatado = new String(arguments, "UTF-8");

            JSONObject jsonRequestPretty = new JSONObject(jsonFormatado);
            
            System.out.println(jsonRequestPretty.toString(4));

            // 2. DESPACHAR PARA O ESQUELETO E RETORNAR O RESULTADO INTERNO
            String resultadoInternoJson = despachante.selecionarEExecutar(jsonFormatado);
            
            // 3. MONTAR O REQUISITO DA MENSAGEM DE REPLICAÇÃO (Coulouris Figura 5.2)
            // Extrai o requestId original para manter a idêntidade da transação RPC
            JSONObject reqOriginal = new JSONObject(jsonFormatado);



            int requestIdOriginal = reqOriginal.optInt("requestId", 0);

            JSONObject envelopeReply = new JSONObject();
            envelopeReply.put("messageType", 1); // 1 = Reply
            envelopeReply.put("requestId", requestIdOriginal);
            envelopeReply.put("objectReference", objectRef);
            envelopeReply.put("methodId", methodId);
            envelopeReply.put("arguments", new JSONObject(resultadoInternoJson)); // Resposta do esqueleto mapeada aqui

            // 4. ENVIAR RESPOSTA (sendReply implicito ao retornar os bytes)

            System.out.println(envelopeReply.toString(4));
            return envelopeReply.toString().getBytes("UTF-8");

        } catch (Exception e) {
            System.err.println("Erro crítico no processamento RPC: " + e.getMessage());
            return "{\"messageType\":1, \"arguments\":{}}".getBytes();
        }
    }
}