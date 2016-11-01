function H_3x3 = computeHomography(src_pts_nx2, dest_pts_nx2)
    src_pts = [src_pts_nx2 ones(size(src_pts_nx2,1),1)];
    num_pts = min([size(src_pts_nx2,1) size(dest_pts_nx2,1)]);

    A = zeros(2*num_pts, 9);
    
    for i=1:num_pts
        A(2*i - 1,1:3) = src_pts(i,:);
        A(2*i,4:6)     = src_pts(i,:);
        A((2*i-1):(2*i), 7:9) = (src_pts(i,:)' * -dest_pts_nx2(i,:))';
    end
    
    [e_vec,e_val] = eig(A'*A);
    [~, i] = min(diag(e_val));
    H_3x3 = reshape(e_vec(:,i), [3,3])';
    H_3x3 = H_3x3 / H_3x3(3,3);
end
