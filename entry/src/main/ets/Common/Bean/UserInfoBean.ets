import FarmBean from './Farmbean';
export default class UserInfoBean {
  Username: string;//用户名
  UserIcon: string;
  UserFarm: FarmBean[];//用户管理的农田列表


  //相当于是初始化函数
  constructor(UserName:string, UserIcon:string, UserFarm:FarmBean[])
  {
    this.Username = UserName
    this.UserIcon = UserIcon
    this.UserFarm = UserFarm
  }
}
