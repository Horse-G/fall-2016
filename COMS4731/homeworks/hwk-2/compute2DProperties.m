function [obj_db, out_img] = compute2DProperties(orig_img, labeled_img)
    obj_count = max(labeled_img(:));
    obj_db = zeros(10,obj_count);
    fh = figure; imshow(orig_img); hold on;
    for i =1:obj_count
        A = 0;
        x_accumulated = 0;
        y_accumulated = 0;
        a = 0;
        b = 0;
        c = 0;
        for j = 1:size(labeled_img,1)
        for k = 1:size(labeled_img,2)
        if labeled_img(j,k) == i
            A = A + 1;
            x_accumulated = x_accumulated + j;
            y_accumulated = y_accumulated + k;
            a = a + j*j;
            b = b + j*k;
            c = c + k*k;
        end
        end
        end
        x_hat = x_accumulated/A;
        y_hat = y_accumulated/A;
        a = a - x_hat*x_hat*A;
        b = 2*b - 4*x_hat*y_hat*A;
        c = c - y_hat*y_hat*A;
        theta1 = atan2(b, a - c)/2;
        theta2 = theta1 + pi/2;
        E1 = a*sin(theta1)*sin(theta1) - b*sin(theta1)*cos(theta1) + c*cos(theta1)*cos(theta1);
        E2 = a*sin(theta2)*sin(theta2) - b*sin(theta2)*cos(theta2) + c*cos(theta2)*cos(theta2);
        if E1 > E2
            Emin = E2;
            Emax = E1;
        else
            Emin = E1;
            Emax = E2;
        end
        roundedness = Emin/Emax;
        line([y_hat y_hat+50*sin(theta2)], [x_hat x_hat+50*cos(theta2)],'LineWidth', 2, 'Color', [1, 0, 0]);
        obj_db(1,i) = i;
        obj_db(2,i) = x_hat;
        obj_db(3,i) = y_hat;
        obj_db(4,i) = Emin;
        obj_db(5,i) = theta1;
        obj_db(6,i) = roundedness;
        obj_db(7,i) = Emax;
        obj_db(8,i) = a;
        obj_db(9,i) = b;
        obj_db(10,i) = c;
    end
    set(fh, 'WindowStyle', 'normal');
    temp_img = getimage(fh);
    truesize(fh, [size(temp_img, 1), size(temp_img, 2)]);
    frame = getframe(fh);
    frame = getframe(fh);
    pause(0.5); 
    out_img = frame.cdata;
    obj_db
end
