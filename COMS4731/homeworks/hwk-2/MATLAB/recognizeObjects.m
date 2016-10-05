function output_img = recognizeObjects(gray_img, labeled_img, database)
    obj_count = size(database,2);
    
    obj_new_count = max(labeled_img(:));
    obj_new_db = zeros(10,obj_new_count);
    fh = figure; imshow(gray_img); hold on;
    for i =1:obj_new_count,
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
        database(1,i) = i;
        database(2,i) = x_hat;
        database(3,i) = y_hat;
        database(4,i) = Emin;
        database(5,i) = theta1;
        database(6,i) = roundedness;
        database(7,i) = Emax;
        database(8,i) = a;
        database(9,i) = b;
        database(10,i) = c;
    end
    
    for i = 1:obj_new_count
    for j = 1:obj_count
        if abs(obj_new_db(6,i)-database(6,j)) < 0.09
            line([y_hat y_hat+50*sin(theta2)], [x_hat x_hat+50*cos(theta2)],'LineWidth', j, 'Color', [1, 0, 0]);
        end
    end
    end
    set(fh, 'WindowStyle', 'normal');
    temp_img = getimage(fh);
    truesize(fh, [size(temp_img, 1), size(temp_img, 2)]);
    frame = getframe(fh);
    frame = getframe(fh);
    pause(0.5); 
    output_img = frame.cdata;
end