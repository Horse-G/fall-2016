function [inliers_id, H] = runRANSAC(Xs, Xd, ransac_n, eps)
    s = 4;
    sample_ct = min([size(Xs,1) size(Xd,1)]);
    final_count = 0;
    
    for i=1:ransac_n
        i_rand = randi(sample_ct, s, 1);
        
        i_H = computeHomography(Xs(i_rand,:), Xd(i_rand,:));
        i_inliers_id = find(sqrt(sum((applyHomography(i_H, Xs)-Xd).^2, 2)) < eps);
        i_count = length(i_inliers_id);
        
        if i_count > final_count
            inliers_id  = i_inliers_id;
            H           = i_H;
            final_count = i_count;
        end
    end
end
