function dest_pts_nx2 = applyHomography(H_3x3, src_pts_nx2)
    num_pts = size(src_pts_nx2,1);
    src_pts = [src_pts_nx2 ones(num_pts,1)];
    dst_pts = zeros(num_pts,3);
    
    dst_pts = (H_3x3 * src_pts')';
    
    for i = 1:num_pts
        dst_pts(i,:) = dst_pts(i,:)./dst_pts(i,3);
    end
    
    dest_pts_nx2 = dst_pts(:,1:2);
end
