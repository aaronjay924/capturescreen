/**
 * @Title: service.java
 * @Copyright (C) 2012 ��ͼ���
 * @Description:
 * @Revision History:
 * @Revision 1.0 2012-8-14  ��־��
 */

package demo;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import sun.misc.BASE64Decoder;

/**
 * @ClassName: service
 * @Description:
 * @author <a href="mailto:jiazhiyu@szlongtu.com">��־��</a> �� 2012-8-14 ����08:29:18
 */

public class service2 extends HttpServlet {

    /**
     * @Fields serialVersionUID :
     */

    private static final long serialVersionUID = 6533716825557540734L;

    /**
     * .
     * <p>
     * Title: doGet
     * </p>
     * <p>
     * Description:
     * </p>
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     * @see javax.servlet.http.HttpServlet#doGet(javax.servlet.http.HttpServletRequest,
     *      javax.servlet.http.HttpServletResponse)
     */
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String dd = req.getParameter("code");
        String path = "showImg.jsp";
        resp.sendRedirect(path);
        generateImage(dd);  //�˴�ʵ�ʿ�����Ӧ���ñ��봮�������ݿ���.demo�����ļ���ȡ�����.
    }

    /**
     * ��Base64���벢�ڱ�������ͼƬ.
     * @param imgStr �����ַ���.
     */
    public void generateImage(String imgStr) {
        if (imgStr == null)// ͼ������Ϊ��
            return;

        BASE64Decoder decoder = new BASE64Decoder();
        try {
            String imgFilePath = "d://base64.txt";// ���base64����
            File file = new File(imgFilePath);
            if (file.isFile()) {
                file.delete();
            }
            OutputStream out1 = new FileOutputStream(imgFilePath);
            out1.write(imgStr.getBytes());
            out1.flush();
            out1.close();
            // Base64����
            byte[] b = decoder.decodeBuffer(imgStr);
            for (int i = 0; i < b.length; ++i) {
                if (b[i] < 0) {// �����쳣����
                    b[i] += 256;
                }
            }
            // ����jpegͼƬ
            String imgFilePath2 = "d://base64.jpg";
            File file2 = new File(imgFilePath2);
            if (file2.isFile()) {
                file2.delete();
            }
            OutputStream out = new FileOutputStream(imgFilePath2);
            out.write(b);
            out.flush();
            out.close();
        } catch (Exception e) {
        }
    }
}
