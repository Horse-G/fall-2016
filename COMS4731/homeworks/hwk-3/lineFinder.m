function line_detected_img = lineFinder(orig_img, hough_img, hough_threshold)
    fh = figure();
    lined_img = orig_img;
    
    rho_num_bins = size(hough_img,1);
    theta_num_bins = size(hough_img,2);
    
    rho_max = sqrt(sum(size(orig_img).^2));
    rho_step = 2*rho_max/rho_num_bins;
    theta_step = 180/theta_num_bins;
    theta_max = 180 - theta_step;
    
    theta = (0:theta_step:theta_max)*(pi/180);
    
    for x = 1:rho_num_bins
    for y = 1:theta_num_bins
    if hough_img(x,y) >= hough_threshold
        
        rho_i = x*rho_step - rho_max;
        theta_i = theta(y);
        
        xs = [1 size(orig_img,2)];
        ys = (xs*sin(theta_i) + rho_i)/cos(theta_i);
        
        line(ys, xs,'LineWidth', 2, 'Color', [1, 0, 0]);
    end
    end
    end
    
    % line printing blackbox
    imshow(lined_img);
    set(fh, 'WindowStyle', 'normal');
    img = getimage(fh);
    truesize(fh, [size(img, 1), size(img, 2)]);
    frame = getframe(fh);
    frame = getframe(fh);
    pause(0.5); 
    line_detected_img = frame.cdata;
    delete(fh);
end
