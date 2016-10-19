function hough_img = generateHoughAccumulator(img, theta_num_bins, rho_num_bins)
    rho_max = sqrt(sum(size(img).^2));
    rho_step = 2*rho_max/rho_num_bins;
    theta_step = 180/theta_num_bins;
    theta_max = 180 - theta_step;
    
    %rho = 1:rho_step:rho_max;
    theta = (0:theta_step:theta_max)*(pi/180);

    hough_img = zeros(rho_num_bins, theta_num_bins);
    
    for x = 1:size(img,1)
    for y = 1:size(img,2)
    if img(x,y) > 0
        phi_row = ceil(((y*cos(theta) - x*sin(theta)) + rho_max)/rho_step);
        for i = 1:theta_num_bins
            idx = rho_num_bins*(i-1) + phi_row(i);
            hough_img(idx) = hough_img(idx) + 1;
        end
    end
    end
    end
    
    hough_img = hough_img*255/max(max(hough_img));
end